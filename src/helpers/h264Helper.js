import { NALU_TYPES } from '../constants';

const h264Helper = {
  naluTypeDisplayed(type) {
    switch (type) {
      case NALU_TYPES.UNSPECIFIED:
        return 'Unspecified';
      case NALU_TYPES.CODED_SLICE_NON_IDR:
        return 'Coded slice a of non-IDR picture';
      case NALU_TYPES.CODED_SLICE_DATA_PARTITION_A:
        return 'Coded slice data partition A';
      case NALU_TYPES.CODED_SLICE_DATA_PARTITION_B:
        return 'Coded slice data partition B';
      case NALU_TYPES.CODED_SLICE_DATA_PARTITION_C:
        return 'Coded slice data partition C';
      case NALU_TYPES.CODED_SLICE_IDR:
        return 'Coded slice of an IDR picture';
      case NALU_TYPES.SEI:
        return 'Supplemental enhancement information (SEI)';
      case NALU_TYPES.SPS:
        return 'Sequence parameter set';
      case NALU_TYPES.PPS:
        return 'Picture parameter set';
      case NALU_TYPES.AUD:
        return 'Access unit delimiter';
      case NALU_TYPES.END_OF_SEQUENCE:
        return 'End of sequence';
      case NALU_TYPES.END_OF_STREAM:
        return 'End of stream';
      case NALU_TYPES.FILLER:
        return 'Filler data';
      case NALU_TYPES.SPS_EXT:
        return 'Sequence parameter set extension';
      case NALU_TYPES.PREFIX_NAL:
        return 'Prefix NAL unit';
      case NALU_TYPES.SUBSET_SPS:
        return 'Subset Sequence parameter set';
      case NALU_TYPES.DPS:
        return 'Depth Parameter Set';
      case NALU_TYPES.CODED_SLICE_AUX:
        return 'Coded slice of an auxiliary coded picture without partitioning';
      case NALU_TYPES.CODED_SLICE_SVC_EXTENSION:
        return 'Coded slice of SVC extension';
      default:
        return 'Unknown';
    }
  },
};

export default h264Helper;
