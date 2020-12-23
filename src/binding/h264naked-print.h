#ifndef H264NAKED_PRINT_H
#define H264NAKED_PRINT_H

#include <sstream>

#include <h264_stream.h>

void print_bytes(std::stringstream &ts, uint8_t* buf, int len);
void print_sps(std::stringstream &ts, sps_t* sps);
void print_pps(std::stringstream &ts, pps_t* pps);
void print_slice_header(std::stringstream &ts, slice_header_t* sh);
void print_aud(std::stringstream &ts, aud_t* aud);
void print_seis(std::stringstream &ts, h264_stream_t* h);
void print_nal(std::stringstream &ts, h264_stream_t* h, nal_t* nal);

#endif
