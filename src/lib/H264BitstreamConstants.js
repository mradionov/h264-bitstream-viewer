export const NALU_TYPES = {
  UNSPECIFIED: 0,
  CODED_SLICE_NON_IDR: 1,
  CODED_SLICE_DATA_PARTITION_A: 2,
  CODED_SLICE_DATA_PARTITION_B: 3,
  CODED_SLICE_DATA_PARTITION_C: 4,
  CODED_SLICE_IDR: 5,
  SEI: 6,
  SPS: 7,
  PPS: 8,
  AUD: 9,
  END_OF_SEQUENCE: 10,
  END_OF_STREAM: 11,
  FILLER: 12,
  SPS_EXT: 13,
  PREFIX_NAL: 14,
  SUBSET_SPS: 15,
  DPS: 16,
  // 17..18 reserved
  CODED_SLICE_AUX: 19,
  CODED_SLICE_SVC_EXTENSION: 20,
  // 20..23 reserved
  // 24..31 unspecified
};

// https://en.wikipedia.org/wiki/Advanced_Video_Coding#Profiles
export const PROFILE_IDC = {
  CAVLC: 44, // CAVLC 4:4:4 Intra Profile (44)
  CBP: 66, // Baseline Profile (BP, 66)
  MP: 77, // Main Profile (MP, 77)
  ScalableBP: 83, // Scalable Baseline Profile (83)
  ScalableHP: 86, // Scalable High Profile (86)
  XP: 88, // Extended Profile (XP, 88)
  HiP: 100, // High Profile (HiP, 100)
  Hi10P: 110, // High 10 Profile (Hi10P, 110)
  MultiviewHP: 118, // Multiview High Profile (118)
  Hi422P: 122, // High 4:2:2 Profile (Hi422P, 122)
  StereoHP: 128, // Stereo High Profile (128)
  MFCHP: 134, // MFC High Profile (134)
  MultiviewDepthHP: 138, // Multiview Depth High Profile (138)
  EnchancedMultiviewDepthHP: 139, // Enhanced Multiview Depth High Profile (139)
  Hi444PP: 244, // High 4:4:4 Predictive Profile (Hi444PP, 244)
};

export const SAR = {
  Extended: 255,
};

export const SLICE_TYPES = {
  P: 0,
  B: 1,
  I: 2,
  EP: 0,
  EB: 1,
  EI: 2,
  SP: 3,
  SI: 4,
  P_ONLY: 5,
  B_ONLY: 6,
  I_ONLY: 7,
  EP_ONLY: 5,
  EB_ONLY: 6,
  EI_ONLY: 7,
  SP_ONLY: 8,
  SI_ONLY: 9,
};

export const SEI_TYPES = {
  BUFFERING_PERIOD: 0,
  PIC_TIMING: 1,
  PAN_SCAN_RECT: 2,
  FILLER_PAYLOAD: 3,
  USER_DATA_REGISTERED_ITU_T_T35: 4,
  USER_DATA_UNREGISTERED: 5,
  RECOVERY_POINT: 6,
  DEC_REF_PIC_MARKING_REPETITION: 7,
  SPARE_PIC: 8,
  SCENE_INFO: 9,
  SUB_SEQ_INFO: 10,
  SUB_SEQ_LAYER_CHARACTERISTICS: 11,
  SUB_SEQ_CHARACTERISTICS: 12,
  FULL_FRAME_FREEZE: 13,
  FULL_FRAME_FREEZE_RELEASE: 14,
  FULL_FRAME_SNAPSHOT: 15,
  PROGRESSIVE_REFINEMENT_SEGMENT_START: 16,
  PROGRESSIVE_REFINEMENT_SEGMENT_END: 17,
  MOTION_CONSTRAINED_SLICE_GROUP_SET: 18,
  FILM_GRAIN_CHARACTERISTICS: 19,
  DEBLOCKING_FILTER_DISPLAY_PREFERENCE: 20,
  STEREO_VIDEO_INFO: 21,
};

export const AUD_PRIMARY_PIC_TYPES = {
  I: 0, // I
  IP: 1, // I, P
  IPB: 2, // I, P, B
  SI: 3, // SI
  SISP: 4, // SI, SP
  ISI: 5, // I, SI
  ISIPSP: 6, // I, SI, P, SP
  ISIPSPB: 7, // I, SI, P, SP, B
};
