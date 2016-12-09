#ifndef PAYLOAD_H_INCLUDED
#define PAYLOAD_H_INCLUDED

#include <stdint.h>

enum PayloadType{
    METEO
};

typedef uint8_t vn_payload_type;
typedef uint8_t vn_payload_version;

typedef struct{
    int16_t temperature;
} vn_meteo_t;

struct Payload{
    vn_payload_type type;
    vn_payload_version version;

    union{
        vn_meteo_t meteo;
    } data;
};

#endif // PAYLOAD_H_INCLUDED
