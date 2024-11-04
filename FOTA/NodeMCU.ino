#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

void crc_8(uint8_t* data,uint16_t len,uint8_t* crc_result);
void crc_32(uint32_t* data,uint16_t len,uint32_t* crc_result);

#define COMMAND 0x22
uint32_t address =  0x08010000;

const char* ssid = "Your Network Name";          
const char* password = "Your Network Password";       

ESP8266WebServer server(80);
const size_t BUFFER_SIZE = 6000; 

void handleFileUpload() {
    HTTPUpload& upload = server.upload();
    
    if (upload.status == UPLOAD_FILE_START) {
        Serial.println("Starting file upload: " + upload.filename);
        // Create or open the file for writing
        File file = SPIFFS.open(upload.filename, "w");
        if (!file) {
            Serial.println("Failed to open file for writing");
            return;
        }
        file.close(); 
    } else if (upload.status == UPLOAD_FILE_WRITE) {
        File file = SPIFFS.open(upload.filename, "a"); 
        if (file) {
            file.write(upload.buf, upload.currentSize);
            file.close();
            Serial.printf("Received %u bytes\n", upload.currentSize);
        } else {
            Serial.println("Failed to open file for appending");
        }
        }
     else if (upload.status == UPLOAD_FILE_END) {
        Serial.printf("Upload complete: %s (%u bytes)\n", upload.filename.c_str(), upload.totalSize);
        server.send(200, "text/plain", "File uploaded successfully!");

        // Read back the file content and print it
        File file = SPIFFS.open(upload.filename, "r");
        if (file) {
            size_t size = file.size();
            Serial.println("Your file size is: " + String(size));
            if (size > BUFFER_SIZE) {
                Serial.println("File too large to read into buffer");
                return; // Handle large file case
            }
            uint8_t* data_buffer = (uint8_t*)malloc(size); // Allocate memory for the buffer
            if (data_buffer == nullptr) {
                Serial.println("Failed to allocate memory for buffer");
                return;
            }
            size_t bytesRead = file.read(data_buffer, size); // Read the entire file into the buffer
            file.close();

            if (bytesRead != size) {
                Serial.println("Error: Bytes read does not match the file size");
            } else {
              uint32_t crc_result_32 {};
              
              crc_32(&address,1,&crc_result_32);
             uint8_t Buffer[8] = {(address >> 24 )&0xFF,(address>>16)&0xFF,(address>>8)&0xFF,address & 0xFF,(crc_result_32 >> 24 ) & 0xFF,(crc_result_32>>16)&0xFF,(crc_result_32 >> 8)&0xFF,crc_result_32&0xFF};
              Serial1.write(0x22);
              delay(100);
              Serial1.write(Buffer,8);
              uint32_t temp_size = bytesRead + 1;
              uint8_t temp_val,number_of_elements {};
              while(temp_size >= 1)
              {
                  temp_size /= 10;
                  number_of_elements++;
              }          
              Serial1.write(number_of_elements);
              temp_size = bytesRead + 1;
              uint8_t temp_buffer1[number_of_elements], temp_buffer2[number_of_elements] {};
              for(int i = 0;i<number_of_elements;i++)
              {
                temp_val = (uint8_t)(temp_size % 10);
                temp_buffer1[i] = (uint8_t)temp_val;
                temp_size /= 10;
              }
              for(int i = (number_of_elements-1), j=0; i >= 0, j<4; i--, j++)
              {
                temp_buffer2[j] = temp_buffer1[i];
              }
              Serial1.write(temp_buffer2,4);
              
              uint8_t crc_result_8 {};
              
              crc_8(data_buffer,bytesRead,&crc_result_8);
              Serial.println(crc_result_8,HEX);
              data_buffer[bytesRead] = crc_result_8;
              Serial1.write(data_buffer,(bytesRead+1));
           
                }
                free(data_buffer);  
            }
        
         else {
            Serial.println("Failed to open file for reading");
        }
    }
}


void handleRoot() {
    File file = SPIFFS.open("/index.html", "r"); 
    if (!file) {
        server.send(404, "text/plain", "File Not Found");
        return;
    }
    server.streamFile(file, "text/html"); // Stream the file to the client
    file.close();
}

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    //Serial1.begin(115200);
    if (!SPIFFS.begin()) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }

    WiFi.begin(ssid, password); // Connect to Wi-Fi
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    Serial.print("IP Address: "); 
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, handleRoot); 
    server.on("/upload", HTTP_POST, []() { server.send(200); }, handleFileUpload); 
    server.begin();
}

void loop() {
    server.handleClient();
}


void crc_8(uint8_t* data,uint16_t len,uint8_t* crc_result)
{
  uint8_t Poly = 0x4C, initial_value = 0xFF;
  *crc_result = initial_value;
  for(int i=0;i<len;i++)
  {
    *crc_result ^= data[i];
    for(int j=0;j<8;j++)
    {
      if(*crc_result & 0x80)
      {
        *crc_result = ((*crc_result) << 1) ^ Poly;
      }
      else
      {
        *crc_result <<= 1;
      }
    }
  }
}


void crc_32(uint32_t* data,uint16_t len,uint32_t* crc_result)
{
  uint32_t Poly = 0x4C11DB7, initial_value = 0xFFFFFFFF;
  *crc_result = initial_value;
  for(int i=0;i<len;i++)
  {
    *crc_result ^= *data;
    for(int j=0;j<32;j++)
    {
      if(*crc_result & 0x80000000)
      {
        *crc_result = ((*crc_result) << 1) ^ Poly;
      }
      else
      {
        *crc_result <<= 1;
      }
    }
  }
}
