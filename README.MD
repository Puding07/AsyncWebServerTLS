# ESPAsyncWebServer TLS Server Example

### Depends on [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)

### Depends on a fixed version of [ESPAsyncTCP](https://github.com/jeroenst/ESPAsyncTCP)

#### Made with the help of **[tom-ch1](https://github.com/tom-ch1)** [comment](https://github.com/me-no-dev/ESPAsyncWebServer/issues/899)

### The [ESP8266fs plugin](https://github.com/esp8266/arduino-esp8266fs-plugin) tool will be in your help.

 ### Steps to make it work:

> 1. Change 0 to 1 at #define ASYNC_TCP_SSL_ENABLED 1 which is at the top of Arduino/libraries/ESPAsyncTCP/src/async_config.h
> 
> 2. Generate key pairs (certificate) to **data folder** in the sketch directory. Don't forget to change **CN= with your Domain name** in the under lying codes.
>	- `openssl genrsa -out Key.pem 1024`
>	- `openssl req -x509 -out Cert.pem -key Key.pem -new -sha256 -subj /CN=your.domain -addext "keyUsage=digitalSignature,keyEncipherment" -addext extendedKeyUsage=serverAuth`
>
> 3. Upload to Flash memory with ESP8266 SPIFFS uploader plugin. The files size are small so you can choose the smallest allocated memory for SPIFFS in Arduino>tools>ESP8266 Sketch Data Upload.
>
> 4. Upload the sketch to your ESP. The recomended CPU frequency is 160Mhz.

**REMEMBER TO ALWAYS GENERATE YOUR OWN KEY PAIRS**

For other questions there is a **[Gitter chat room](https://gitter.im/me-no-dev/ESPAsyncWebServer)** for the repo.

Do not thank to me, I just created the TLS example based on documentations and a lot of tries.

### Thank to **[me-no-dev](https://github.com/me-no-dev)** and **[tom-ch1](https://github.com/tom-ch1)** and **[jeroenst](https://github.com/jeroenst)**.
