<template>
  <div>
    <PayloadPPS
      v-if="payload.header.type === NALU_TYPES.PPS"
      :payload="payload"
    />
    <PayloadSPS
      v-else-if="payload.header.type === NALU_TYPES.SPS"
      :payload="payload"
    />
    <PayloadSliceHeader
      v-else-if="payload.header.type === NALU_TYPES.CODED_SLICE_NON_IDR"
      :payload="payload"
    />
    <PayloadNaked v-else-if="typeof payload === 'string'" :payload="payload" />
  </div>
</template>

<script>
import { NALU_TYPES } from '../../lib';

import PayloadNaked from './PayloadNaked';
import PayloadSPS from './PayloadSPS';
import PayloadPPS from './PayloadPPS';
import PayloadSliceHeader from './PayloadSliceHeader';

export default {
  components: {
    PayloadNaked,
    PayloadSPS,
    PayloadPPS,
    PayloadSliceHeader,
  },

  props: {
    payload: {
      type: Object,
    },
  },

  data() {
    return {
      NALU_TYPES,
    };
  },
};
</script>

<style module></style>
