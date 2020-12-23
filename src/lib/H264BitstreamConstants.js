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
  P: 0, // P (P slice)
  B: 1, // B (B slice)
  I: 2, // I (I slice)
  EP: 0, // EP (EP slice)
  EB: 1, // EB (EB slice)
  EI: 2, // EI (EI slice)
  SP: 3, // SP (SP slice)
  SI: 4, // SI (SI slice)
  P_ONLY: 5, // P (P slice)
  B_ONLY: 6, // B (B slice)
  I_ONLY: 7, // I (I slice)
  EP_ONLY: 5, // EP (EP slice)
  EB_ONLY: 6, // EB (EB slice)
  EI_ONLY: 7, // EI (EI slice)
  SP_ONLY: 8, // SP (SP slice)
  SI_ONLY: 9, // SI (SI slice)
};
