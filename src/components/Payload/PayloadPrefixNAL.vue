<template>
  <Table>
    <HeaderRow>
      <HeaderCell colspan="2">
        Prefix NAL SVC
      </HeaderCell>
    </HeaderRow>
    <template v-if="header.refIdc !== 0">
      <Row>
        <Cell>store_ref_base_pic_flag</Cell>
        <Cell>{{ Number(prefix_nal_svc.store_ref_base_pic_flag) }}</Cell>
      </Row>
      <template
        v-if="
          (nal_svc_ext.use_ref_base_pic_flag ||
            prefix_nal_svc.store_ref_base_pic_flag) &&
            !nal_svc_ext.idr_flag
        "
      >
        <TodoRow tag="read_debug_dec_ref_base_pic_marking" />
      </template>
      <Row>
        <Cell>additional_prefix_nal_unit_extension_flag</Cell>
        <Cell>
          {{ Number(prefix_nal_svc.additional_prefix_nal_unit_extension_flag) }}
        </Cell>
      </Row>
      <template v-if="prefix_nal_svc.additional_prefix_nal_unit_extension_flag">
        <Row>
          <Cell>additional_prefix_nal_unit_extension_data_flag</Cell>
          <Cell>
            {{
              Number(
                prefix_nal_svc.additional_prefix_nal_unit_extension_data_flag,
              )
            }}
          </Cell>
        </Row>
      </template>
    </template>
    <Row>
      <Cell>additional_prefix_nal_unit_extension_data_flag</Cell>
      <Cell>
        {{
          Number(prefix_nal_svc.additional_prefix_nal_unit_extension_data_flag)
        }}
      </Cell>
    </Row>
  </Table>
</template>

<script>
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
  computed: {
    header() {
      return this.payload.header;
    },
    prefix_nal_svc() {
      return this.payload.prefix_nal_svc;
    },
    nal_svc_ext() {
      return this.payload.nal_svc_ext;
    },
  },
};
</script>
