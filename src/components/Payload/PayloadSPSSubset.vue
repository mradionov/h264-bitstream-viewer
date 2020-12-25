<template>
  <div>
    <PayloadSPS :sps="sps" />
    <template v-if="sps.profile_idc === 83 || sps.profile_idc === 86">
      <Table>
        <HeaderRow>
          <HeaderCell colspan="2">SPS SVC Extension</HeaderCell>
        </HeaderRow>
        <Row>
          <Cell>inter_layer_deblocking_filter_control_present_flag</Cell>
          <Cell>{{
            Number(
              sps_svc_ext.inter_layer_deblocking_filter_control_present_flag,
            )
          }}</Cell>
        </Row>
        <Row>
          <Cell>extended_spatial_scalability_idc</Cell>
          <Cell>{{ sps_svc_ext.extended_spatial_scalability_idc }}</Cell>
        </Row>
        <template
          v-if="sps.chroma_format_idc === 1 || sps.chroma_format_idc == 2"
        >
          <Row>
            <Cell>chroma_phase_x_plus1_flag</Cell>
            <Cell>{{ Number(sps_svc_ext.chroma_phase_x_plus1_flag) }}</Cell>
          </Row>
        </template>
        <template v-if="sps.chroma_format_idc === 1">
          <Row>
            <Cell>chroma_phase_y_plus1</Cell>
            <Cell>{{ sps_svc_ext.chroma_phase_y_plus1 }}</Cell>
          </Row>
        </template>
        <template v-if="sps_svc_ext.extended_spatial_scalability_idc">
          <template v-if="sps.chroma_format_idc > 0">
            <Row>
              <Cell>seq_ref_layer_chroma_phase_x_plus1_flag</Cell>
              <Cell>{{
                Number(sps_svc_ext.seq_ref_layer_chroma_phase_x_plus1_flag)
              }}</Cell>
            </Row>
            <Row>
              <Cell>seq_ref_layer_chroma_phase_y_plus1</Cell>
              <Cell>{{
                Number(sps_svc_ext.seq_ref_layer_chroma_phase_y_plus1)
              }}</Cell>
            </Row>
          </template>
          <Row>
            <Cell>seq_scaled_ref_layer_left_offset</Cell>
            <Cell>{{ sps_svc_ext.seq_scaled_ref_layer_left_offset }}</Cell>
          </Row>
          <Row>
            <Cell>seq_scaled_ref_layer_top_offset</Cell>
            <Cell>{{ sps_svc_ext.seq_scaled_ref_layer_top_offset }}</Cell>
          </Row>
          <Row>
            <Cell>seq_scaled_ref_layer_right_offset</Cell>
            <Cell>{{ sps_svc_ext.seq_scaled_ref_layer_right_offset }}</Cell>
          </Row>
          <Row>
            <Cell>seq_scaled_ref_layer_bottom_offset</Cell>
            <Cell>{{ sps_svc_ext.seq_scaled_ref_layer_bottom_offset }}</Cell>
          </Row>
        </template>
        <Row>
          <Cell>seq_tcoeff_level_prediction_flag</Cell>
          <Cell>
            {{ Number(sps_svc_ext.seq_tcoeff_level_prediction_flag) }}
          </Cell>
        </Row>
        <template v-if="sps_svc_ext.seq_tcoeff_level_prediction_flag">
          <Row>
            <Cell>adaptive_tcoeff_level_prediction_flag</Cell>
            <Cell>
              {{ Number(sps_svc_ext.adaptive_tcoeff_level_prediction_flag) }}
            </Cell>
          </Row>
        </template>
        <Row>
          <Cell>slice_header_restriction_flag</Cell>
          <Cell>{{ Number(sps_svc_ext.slice_header_restriction_flag) }}</Cell>
        </Row>
        <Row>
          <Cell>svc_vui_parameters_present_flag</Cell>
          <Cell>{{ Number(sps_svc_ext.svc_vui_parameters_present_flag) }}</Cell>
        </Row>
        <template v-if="sps_svc_ext.svc_vui_parameters_present_flag">
          <TodoRow tag="read_debug_svc_vui_parameters_extension" />
        </template>
      </Table>
    </template>
    <Table>
      <HeaderRow>
        <HeaderCell colspan="2">SPS Subset</HeaderCell>
      </HeaderRow>
      <Row>
        <Cell>additional_extension2_flag</Cell>
        <Cell>{{ Number(sps_subset.additional_extension2_flag) }}</Cell>
      </Row>
    </Table>
  </div>
</template>

<script>
import { PROFILE_IDC, SAR } from '../../lib';

import { Table, Row, Cell, HeaderRow, HeaderCell, TodoRow } from '../Table';

import PayloadSPS from './PayloadSPS';

export default {
  components: {
    PayloadSPS,
    Table,
    Row,
    Cell,
    HeaderRow,
    HeaderCell,
    TodoRow,
  },
  props: {
    sps_subset: Object,
  },
  computed: {
    sps() {
      return this.sps_subset.sps;
    },
    sps_svc_ext() {
      return this.sps_subset.sps_svc_ext;
    },
  },
};
</script>

<style module></style>
