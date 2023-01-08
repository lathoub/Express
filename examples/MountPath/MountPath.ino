#include <Express.h>
using namespace EXPRESS_NAMESPACE;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

Express app;
Express v1;
Express v2;

void setup() {
  Serial.begin(115200);
  while (!Serial && !Serial.available()) {} delay(250);
  Serial.println(F("booting"));

  Ethernet.begin(mac);

  app.use("/v1", v1);
  app.use("/v2", v2);

  app.get("/user", [](Request &req, Response &res) { 
    res.status(HTTP_STATUS_OK).send("root path");
  });

  // Landing page here is /v1/user
  v1.get("/user", [](Request &req, Response &res) { 
    res.status(HTTP_STATUS_OK).send("route v1");
  });

  // Landing page here is /v2/user
  v2.get("/user", [](Request &req, Response &res) { 
    res.status(HTTP_STATUS_OK).send("route v2");
  });

  app.listen(80, []() {
    Serial.print(F("Example app listening on port "));
    Serial.print(Ethernet.localIP());
    Serial.print(F(" "));
    Serial.println(app.port);
  });
}

void loop() {
  app.run();
}