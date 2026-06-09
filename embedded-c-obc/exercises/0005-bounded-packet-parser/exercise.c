#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

enum {
    OBC_SOF0 = 0xa5u,
    OBC_SOF1 = 0x5au,
    OBC_MAX_PAYLOAD_LEN = 8u,
    OBC_FIXED_HEADER_LEN = 4u,
    OBC_CHECKSUM_LEN = 1u,
    OBC_MIN_FRAME_LEN = OBC_FIXED_HEADER_LEN + OBC_CHECKSUM_LEN
};

typedef struct {
    uint8_t msg_id;
    uint8_t payload_len;
    uint8_t payload[OBC_MAX_PAYLOAD_LEN];
} ObcPacket;

static uint8_t obc_checksum(const uint8_t *bytes, size_t len)
{
    uint8_t count = 0;

    size_t i;
    for (i = 0; i < len; i++){
        count += bytes[i];
    }


    return count;
}

static bool obc_parse_frame(const uint8_t *frame, size_t frame_len, ObcPacket *out)
{


    if (frame == NULL || out == NULL)
    {
        return false;
    }

    if (frame_len < OBC_MIN_FRAME_LEN)
    {
        return false;
    }

    if (frame[0] != OBC_SOF0 || frame[1] != OBC_SOF1)
    {
        return false;
    }

    uint8_t payload_len = frame[3];

    if (payload_len > OBC_MAX_PAYLOAD_LEN)
    {
        return false;
    }

    size_t expected_frame_len = OBC_FIXED_HEADER_LEN + OBC_CHECKSUM_LEN + payload_len;

    if (frame_len != expected_frame_len)
    {
        return false;
    }

    size_t checksum_index   = frame_len - OBC_CHECKSUM_LEN;
    uint8_t checksum        = frame[checksum_index];

    if (obc_checksum(&frame[2], 2u + payload_len) != checksum)
    {
        return false;
    }


    out->msg_id         = frame[2];
    out->payload_len    = frame[3];

    size_t i;
    size_t out_index = 0;
    for (i = 4; i < checksum_index; i ++)
    {
        out->payload[out_index] = frame[i];
        out_index ++;
    }

    return true;


}

int main(void)
{
    const uint8_t valid[] = {
        OBC_SOF0, OBC_SOF1, 0x10u, 0x03u, 0x01u, 0x02u, 0x03u, 0x19u
    };
    const uint8_t valid_empty[] = {
        OBC_SOF0, OBC_SOF1, 0x22u, 0x00u, 0x22u
    };
    const uint8_t bad_sof[] = {
        0x00u, OBC_SOF1, 0x10u, 0x01u, 0xaau, 0xbbu
    };
    const uint8_t too_large_payload[] = {
        OBC_SOF0, OBC_SOF1, 0x10u, 0x09u,
        0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 0x31u
    };
    const uint8_t truncated[] = {
        OBC_SOF0, OBC_SOF1, 0x10u, 0x03u, 0x01u, 0x02u
    };
    const uint8_t bad_checksum[] = {
        OBC_SOF0, OBC_SOF1, 0x10u, 0x03u, 0x01u, 0x02u, 0x03u, 0x00u
    };

    ObcPacket packet = {0};

    assert(obc_checksum(&valid[2], 5u) == 0x19u);
    assert(obc_checksum(&valid_empty[2], 2u) == 0x22u);

    assert(!obc_parse_frame(NULL, sizeof(valid), &packet));
    assert(!obc_parse_frame(valid, sizeof(valid), NULL));
    assert(!obc_parse_frame(valid, 2u, &packet));
    assert(!obc_parse_frame(bad_sof, sizeof(bad_sof), &packet));
    assert(!obc_parse_frame(too_large_payload, sizeof(too_large_payload), &packet));
    assert(!obc_parse_frame(truncated, sizeof(truncated), &packet));
    assert(!obc_parse_frame(bad_checksum, sizeof(bad_checksum), &packet));

    assert(obc_parse_frame(valid, sizeof(valid), &packet));
    assert(packet.msg_id == 0x10u);
    assert(packet.payload_len == 3u);
    assert(packet.payload[0] == 0x01u);
    assert(packet.payload[1] == 0x02u);
    assert(packet.payload[2] == 0x03u);

    assert(obc_parse_frame(valid_empty, sizeof(valid_empty), &packet));
    assert(packet.msg_id == 0x22u);
    assert(packet.payload_len == 0u);

    puts("PASS: bounded packet parser exercise");
    return 0;
}
