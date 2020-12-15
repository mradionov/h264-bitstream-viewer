#include <array>
#include <vector>

#include <emscripten.h>
#include <emscripten/bind.h>

#include <h264_stream.h>

#include "reader.h"

using array_int_2 = std::array<int, 2>;
using array_int_6 = std::array<int, 6>;
using array_int_8 = std::array<int, 8>;
using array_int_96 = std::array<int, 96>;
using array_int_128 = std::array<int, 128>;
using array_int_256 = std::array<int, 256>;

template<
  typename Result,
  typename ValueObject,
  typename FieldType,
  size_t N,
  size_t M,
  FieldType ValueObject::*member
>
Result readArray2d(const ValueObject& vobj) {
  Result arr1d;

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      arr1d[i * M + j] = (vobj.*member)[i][j];
    }
  }

  return arr1d;
}

template<typename Result, typename ValueObject>
void writeArray2d(ValueObject& vobj, Result) {}

// Template metaprogramming used to register elements for array bindings.
// Otherwise you will have to manually mention all of them, which is tedious.
// Taken from:
// http://nnarain.github.io/2019/01/19/GameboyCore-in-the-Web!.html
template<typename ArrayT, size_t N>
struct ArrayInitializer : public ArrayInitializer<ArrayT, N-1>
{
  explicit ArrayInitializer(emscripten::value_array<ArrayT>& arr)
    : ArrayInitializer<ArrayT, N-1>{arr}
  {
    arr.element(emscripten::index<N-1>());
  }
};

template<typename ArrayT>
struct ArrayInitializer<ArrayT, 0>
{
  explicit ArrayInitializer(emscripten::value_array<ArrayT>& arr)
  {
  }
};

extern "C" {

EMSCRIPTEN_BINDINGS(H264Bitstream) {

  emscripten::class_<Reader>("Reader")
    .constructor<>()
    .function("readNaked", &Reader::readNaked)
    .function("readPPS", &Reader::readPPS)
  ;

  emscripten::value_array<array_int_2> def_array_int_2("array_int_2");
  ArrayInitializer<array_int_2, 2>{def_array_int_2};

  emscripten::value_array<array_int_6> def_array_int_6("array_int_6");
  ArrayInitializer<array_int_6, 6>{def_array_int_6};

  emscripten::value_array<array_int_8> def_array_int_8("array_int_8");
  ArrayInitializer<array_int_8, 8>{def_array_int_8};

  emscripten::value_array<array_int_96> def_array_int_96("array_int_96");
  ArrayInitializer<array_int_96, 96>{def_array_int_96};

  emscripten::value_array<array_int_128> def_array_int_128("array_int_128");
  ArrayInitializer<array_int_128, 128>{def_array_int_128};

  emscripten::value_array<array_int_256> def_array_int_256("array_int_256");
  ArrayInitializer<array_int_256, 256>{def_array_int_256};

  emscripten::value_object<pps_t>("pps_t")
    .field("pic_parameter_set_id", &pps_t::pic_parameter_set_id)
    .field("seq_parameter_set_id", &pps_t::seq_parameter_set_id)
    .field("entropy_coding_mode_flag", &pps_t::entropy_coding_mode_flag)
    .field("pic_order_present_flag", &pps_t::pic_order_present_flag)
    .field("num_slice_groups_minus1", &pps_t::num_slice_groups_minus1)
    .field("slice_group_map_type", &pps_t::slice_group_map_type)
    .field("run_length_minus1", &pps_t::run_length_minus1)
    .field("top_left", &pps_t::top_left)
    .field("bottom_right", &pps_t::bottom_right)
    .field(
      "slice_group_change_direction_flag",
      &pps_t::slice_group_change_direction_flag
    )
    .field(
      "slice_group_change_rate_minus1",
      &pps_t::slice_group_change_rate_minus1
    )
    .field("pic_size_in_map_units_minus1", &pps_t::pic_size_in_map_units_minus1)
    .field("slice_group_id", &pps_t::slice_group_id)
    .field("num_ref_idx_l0_active_minus1", &pps_t::num_ref_idx_l0_active_minus1)
    .field("num_ref_idx_l1_active_minus1", &pps_t::num_ref_idx_l1_active_minus1)
    .field("weighted_pred_flag", &pps_t::weighted_pred_flag)
    .field("weighted_bipred_idc", &pps_t::weighted_bipred_idc)
    .field("pic_init_qp_minus26", &pps_t::pic_init_qp_minus26)
    .field("pic_init_qs_minus26", &pps_t::pic_init_qs_minus26)
    .field("chroma_qp_index_offset", &pps_t::chroma_qp_index_offset)
    .field(
      "deblocking_filter_control_present_flag",
      &pps_t::deblocking_filter_control_present_flag
    )
    .field("constrained_intra_pred_flag", &pps_t::constrained_intra_pred_flag)
    .field(
      "redundant_pic_cnt_present_flag",
      &pps_t::redundant_pic_cnt_present_flag
    )
    .field("transform_8x8_mode_flag", &pps_t::transform_8x8_mode_flag)
    .field(
      "pic_scaling_matrix_present_flag",
      &pps_t::pic_scaling_matrix_present_flag
    )
    .field(
      "pic_scaling_list_present_flag",
      &pps_t::pic_scaling_list_present_flag
    )
    .field(
      "ScalingList4x4",
      &readArray2d<
        array_int_96, pps_t, int[6][16], 6, 16, &pps_t::ScalingList4x4
      >,
      &writeArray2d<array_int_96, pps_t>
    )
    .field(
      "UseDefaultScalingMatrix4x4Flag",
      &pps_t::UseDefaultScalingMatrix4x4Flag
    )
    .field(
      "ScalingList8x8",
      &readArray2d<
        array_int_128, pps_t, int[2][64], 2, 64, &pps_t::ScalingList8x8
      >,
      &writeArray2d<array_int_128, pps_t>
    )
    .field(
      "UseDefaultScalingMatrix8x8Flag",
      &pps_t::UseDefaultScalingMatrix8x8Flag
    )
    .field(
      "second_chroma_qp_index_offset",
      &pps_t::second_chroma_qp_index_offset
    )
  ;
};

}
