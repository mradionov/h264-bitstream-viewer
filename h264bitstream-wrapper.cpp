#include <iostream>
#include <sstream>

#include <emscripten.h>
#include <emscripten/bind.h>

#include <h264_stream.h>

// using namespace emscripten;
using namespace std;

extern "C" {

void print_bytes(stringstream &ss, uint8_t* buf, int len) {
  for (int i = 0; i < len; i++) {
    // ss << string("%1 ").arg(buf[i] , 0, 16, QLatin1Char('0'));
    ss << hex << buf[i] << " ";

    if ((i+1) % 16 == 0) {
      ss<< "\n";
    }
  }
  ss << "\n";
}

void print_seis(stringstream &ss, h264_stream_t* h) {
  sei_t** seis = h->seis;
  int num_seis = h->num_seis;

  cout << "num_seis = " << num_seis << endl;

  ss << "======= SEI =======\n";
  const char* sei_type_name;
  int i;
  for (i = 0; i < num_seis; i++) {
    sei_t* s = seis[i];
    switch(s->payloadType) {
      case SEI_TYPE_BUFFERING_PERIOD :          sei_type_name = "Buffering period"; break;
      case SEI_TYPE_PIC_TIMING :                sei_type_name = "Pic timing"; break;
      case SEI_TYPE_PAN_SCAN_RECT :             sei_type_name = "Pan scan rect"; break;
      case SEI_TYPE_FILLER_PAYLOAD :            sei_type_name = "Filler payload"; break;
      case SEI_TYPE_USER_DATA_REGISTERED_ITU_T_T35 : sei_type_name = "User data registered ITU-T T35"; break;
      case SEI_TYPE_USER_DATA_UNREGISTERED :    sei_type_name = "User data unregistered"; break;
      case SEI_TYPE_RECOVERY_POINT :            sei_type_name = "Recovery point"; break;
      case SEI_TYPE_DEC_REF_PIC_MARKING_REPETITION : sei_type_name = "Dec ref pic marking repetition"; break;
      case SEI_TYPE_SPARE_PIC :                 sei_type_name = "Spare pic"; break;
      case SEI_TYPE_SCENE_INFO :                sei_type_name = "Scene info"; break;
      case SEI_TYPE_SUB_SEQ_INFO :              sei_type_name = "Sub seq info"; break;
      case SEI_TYPE_SUB_SEQ_LAYER_CHARACTERISTICS : sei_type_name = "Sub seq layer characteristics"; break;
      case SEI_TYPE_SUB_SEQ_CHARACTERISTICS :   sei_type_name = "Sub seq characteristics"; break;
      case SEI_TYPE_FULL_FRAME_FREEZE :         sei_type_name = "Full frame freeze"; break;
      case SEI_TYPE_FULL_FRAME_FREEZE_RELEASE : sei_type_name = "Full frame freeze release"; break;
      case SEI_TYPE_FULL_FRAME_SNAPSHOT :       sei_type_name = "Full frame snapshot"; break;
      case SEI_TYPE_PROGRESSIVE_REFINEMENT_SEGMENT_START : sei_type_name = "Progressive refinement segment start"; break;
      case SEI_TYPE_PROGRESSIVE_REFINEMENT_SEGMENT_END : sei_type_name = "Progressive refinement segment end"; break;
      case SEI_TYPE_MOTION_CONSTRAINED_SLICE_GROUP_SET : sei_type_name = "Motion constrained slice group set"; break;
      case SEI_TYPE_FILM_GRAIN_CHARACTERISTICS : sei_type_name = "Film grain characteristics"; break;
      case SEI_TYPE_DEBLOCKING_FILTER_DISPLAY_PREFERENCE : sei_type_name = "Deblocking filter display preference"; break;
      case SEI_TYPE_STEREO_VIDEO_INFO :         sei_type_name = "Stereo video info"; break;
      default: sei_type_name = "Unknown"; break;
    }
    ss << "=== " << sei_type_name<<"===\n";
    ss << " payloadType :" << s->payloadType <<"\n";
    ss << " payloadSize :" << s->payloadSize <<"\n";

    ss << " payload : \n";
    print_bytes(ss, s->data, s->payloadSize);
  }
}

struct Reader {
  Reader() {}

  string readSEI(uintptr_t input, int size) {
    const int32_t* data = reinterpret_cast<int32_t*>(input);

    uint8_t* buf = new uint8_t[size];

    for (int i = 0; i < size; i += 1) {
      buf[i] = (uint8_t) (data[i] & 0xff);
    }

    h264_stream_t* h = h264_new();

    int ret = read_nal_unit(h, buf, size);

    cout << "ret = " << ret << endl;

    stringstream ss;

    print_seis(ss, h);

    cout << ss.str() << endl;

    h264_free(h);

    delete [] buf;

    return ss.str();
  }
};


EMSCRIPTEN_BINDINGS(H264Bitstream) {

  emscripten::class_<Reader>("Reader")
    .constructor<>()
    .function("readSEI", &Reader::readSEI)
    ;

}

}
