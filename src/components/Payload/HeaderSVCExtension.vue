<template>
  <div>
    <Table>
      <HeaderRow>
        <HeaderCell colspan="2">
          NAL
        </HeaderCell>
      </HeaderRow>
      <template v-if="header.type !== 21">
        <Row>
          <Cell>svc_extension_flag</Cell>
          <Cell>1</Cell>
        </Row>
      </template>
      <template v-else>
        <Row>
          <Cell>avc_3d_extension_flag</Cell>
          <Cell>1</Cell>
        </Row>
      </template>
    </Table>
    <Table>
      <HeaderRow>
        <HeaderCell colspan="2">
          NAL SVC Extension
        </HeaderCell>
      </HeaderRow>
      <Row>
        <Cell>idr_flag</Cell>
        <Cell>{{ Number(nal_svc_ext.idr_flag) }}</Cell>
      </Row>
      <Row>
        <Cell>priority_id</Cell>
        <Cell>{{ nal_svc_ext.priority_id }}</Cell>
      </Row>
      <Row>
        <Cell>no_inter_layer_pred_flag</Cell>
        <Cell>{{ Number(nal_svc_ext.no_inter_layer_pred_flag) }}</Cell>
      </Row>
      <Row>
        <Cell>dependency_id</Cell>
        <Cell>{{ nal_svc_ext.dependency_id }}</Cell>
      </Row>
      <Row>
        <Cell>quality_id</Cell>
        <Cell>{{ nal_svc_ext.quality_id }}</Cell>
      </Row>
      <Row>
        <Cell>temporal_id</Cell>
        <Cell>{{ nal_svc_ext.temporal_id }}</Cell>
      </Row>
      <Row>
        <Cell>use_ref_base_pic_flag</Cell>
        <Cell>{{ Number(nal_svc_ext.use_ref_base_pic_flag) }}</Cell>
      </Row>
      <Row>
        <Cell>discardable_flag</Cell>
        <Cell>{{ Number(nal_svc_ext.discardable_flag) }}</Cell>
      </Row>
      <Row>
        <Cell>output_flag</Cell>
        <Cell>{{ Number(nal_svc_ext.output_flag) }}</Cell>
      </Row>
      <Row>
        <Cell>reserved_three_2bits</Cell>
        <Cell>{{ nal_svc_ext.reserved_three_2bits }}</Cell>
      </Row>
    </Table>
  </div>
</template>

<script>
import { NALU_TYPES } from '../../lib';

import { Table, Row, Cell, HeaderRow, HeaderCell, TodoRow } from '../Table';

export default {
  components: {
    Table,
    Row,
    Cell,
    HeaderRow,
    HeaderCell,
    TodoRow,
  },
  props: {
    payload: Object,
  },

  data() {
    return {
      NALU_TYPES,
    };
  },

  computed: {
    header() {
      return this.payload.header;
    },
    nal_svc_ext() {
      return this.payload.nal_svc_ext;
    },
  },
};
</script>
