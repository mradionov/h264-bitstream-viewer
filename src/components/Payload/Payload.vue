<template>
  <div>
    <HeaderSVCExtension
      v-if="
        type === NALU_TYPES.PREFIX_NAL ||
          type === NALU_TYPES.CODED_SLICE_SVC_EXTENSION ||
          type === 21
      "
      :payload="payload"
    />
    <PayloadPPS v-if="type === NALU_TYPES.PPS" :payload="payload" />
    <PayloadSPS v-else-if="type === NALU_TYPES.SPS" :sps="payload.sps" />
    <PayloadSliceHeader
      v-else-if="
        type === NALU_TYPES.CODED_SLICE_IDR ||
          type === NALU_TYPES.CODED_SLICE_NON_IDR ||
          type === NALU_TYPES.CODED_SLICE_AUR
      "
      :payload="payload"
    />
    <PayloadSEI v-else-if="type === NALU_TYPES.SEI" :payload="payload" />
    <PayloadSliceHeader
      v-else-if="type === NALU_TYPES.CODED_SLICE_SVC_EXTENSION"
      :payload="payload"
    />
    <PayloadSPSSubset
      v-else-if="type === NALU_TYPES.SUBSET_SPS"
      :sps_subset="payload.sps_subset"
    />
    <PayloadPrefixNAL
      v-else-if="type === NALU_TYPES.PREFIX_NAL"
      :payload="payload"
    />
    <PayloadAUD v-else-if="type === NALU_TYPES.AUD" :payload="payload" />
    <PayloadMissing v-else :payload="payload" />
  </div>
</template>

<script>
import { NALU_TYPES } from '../../lib';

import HeaderSVCExtension from './HeaderSVCExtension';
import PayloadAUD from './PayloadAUD';
import PayloadSPS from './PayloadSPS';
import PayloadPPS from './PayloadPPS';
import PayloadSEI from './PayloadSEI';
import PayloadSliceHeader from './PayloadSliceHeader';
import PayloadSPSSubset from './PayloadSPSSubset';
import PayloadPrefixNAL from './PayloadPrefixNAL';
import PayloadMissing from './PayloadMissing';

export default {
  components: {
    HeaderSVCExtension,
    PayloadAUD,
    PayloadSPS,
    PayloadPPS,
    PayloadSEI,
    PayloadSliceHeader,
    PayloadSPSSubset,
    PayloadPrefixNAL,
    PayloadMissing,
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
    type() {
      return this.payload.header.type;
    },
  },
};
</script>
