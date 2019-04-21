import { NAL_UNIT_TYPES } from '../constants';

const nalHelper = {

  nalTypeDisplayed(type) {
    switch (type) {
      case NAL_UNIT_TYPES.UNSPECIFIED:
        return 'Unspecified';
      case NAL_UNIT_TYPES.CODED_SLICE_NON_IDR:
        return 'Coded slice a of non-IDR picture';
      case NAL_UNIT_TYPES.CODED_SLICE_DATA_PARTITION_A:
        return 'Coded slice data partition A';
      case NAL_UNIT_TYPES.CODED_SLICE_DATA_PARTITION_B:
        return 'Coded slice data partition B';
      case NAL_UNIT_TYPES.CODED_SLICE_DATA_PARTITION_C:
        return 'Coded slice data partition C';
      case NAL_UNIT_TYPES.CODED_SLICE_IDR:
        return 'Coded slice of an IDR picture';
      case NAL_UNIT_TYPES.SEI:
        return 'Supplemental enhancement information (SEI)';
      case NAL_UNIT_TYPES.SPS:
        return 'Sequence parameter set';
      case NAL_UNIT_TYPES.PPS:
        return 'Picture parameter set';
      case NAL_UNIT_TYPES.AUD:
        return 'Access unit delimiter';
      case NAL_UNIT_TYPES.END_OF_SEQUENCE:
        return 'End of sequence';
      case NAL_UNIT_TYPES.END_OF_STREAM:
        return 'End of stream';
      case NAL_UNIT_TYPES.FILLER:
        return 'Filler data';
      case NAL_UNIT_TYPES.SPS_EXT:
        return 'Sequence parameter set extension';
      case NAL_UNIT_TYPES.PREFIX_NAL:
        return 'Prefix NAL unit';
      case NAL_UNIT_TYPES.SUBSET_SPS:
        return 'Subset Sequence parameter set';
      case NAL_UNIT_TYPES.DPS:
        return 'Depth Parameter Set';
      case NAL_UNIT_TYPES.CODED_SLICE_AUX:
        return 'Coded slice of an auxiliary coded picture without partitioning';
      case NAL_UNIT_TYPES.CODED_SLICE_SVC_EXTENSION:
        return 'Coded slice of SVC extension';
      default:
        return 'Unknown';
    }
  },

};

export default nalHelper;
