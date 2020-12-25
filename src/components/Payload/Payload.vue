<template>
  <div>
    <PayloadPPS
      v-if="payload.header.type === NALU_TYPES.PPS"
      :payload="payload"
    />
    <PayloadSPS
      v-else-if="payload.header.type === NALU_TYPES.SPS"
      :sps="payload.sps"
    />
    <PayloadSliceHeader
      v-else-if="
        payload.header.type === NALU_TYPES.CODED_SLICE_IDR ||
          payload.header.type === NALU_TYPES.CODED_SLICE_NON_IDR ||
          payload.header.type === NALU_TYPES.CODED_SLICE_AUR
      "
      :payload="payload"
    />
    <PayloadSEI
      v-else-if="payload.header.type === NALU_TYPES.SEI"
      :payload="payload"
    />
    <PayloadSliceHeader
      v-else-if="payload.header.type === NALU_TYPES.CODED_SLICE_SVC_EXTENSION"
      :payload="payload"
    />
    <PayloadSPSSubset
      v-else-if="payload.header.type === NALU_TYPES.SUBSET_SPS"
      :sps_subset="payload.sps_subset"
    />
    <PayloadNaked v-else-if="payload.naked.length > 0" :payload="payload" />
    <PayloadMissing v-else :payload="payload" />
  </div>
</template>

<script>
import { NALU_TYPES } from '../../lib';

import PayloadSPS from './PayloadSPS';
import PayloadPPS from './PayloadPPS';
import PayloadSEI from './PayloadSEI';
import PayloadSliceHeader from './PayloadSliceHeader';
import PayloadSPSSubset from './PayloadSPSSubset';
import PayloadMissing from './PayloadMissing';
import PayloadNaked from './PayloadNaked';

export default {
  components: {
    PayloadSPS,
    PayloadPPS,
    PayloadSEI,
    PayloadSliceHeader,
    PayloadSPSSubset,
    PayloadNaked,
    PayloadMissing,
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
