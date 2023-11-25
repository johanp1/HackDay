/******************************************************************************
 * COPYRIGHT (c) Volvo Corporation 2020
 *
 * The copyright of the computer program(s) herein is the property of Volvo
 * Corporation, Sweden. The programs may be used and copied only with the
 * written permission from Volvo Corporation, or in accordance with the terms
 * and conditions stipulated in the agreement contract under which the
 * program(s) have been supplied.
 *
 *****************************************************************************/
/**
 * @addtogroup   LDC_VehicleMotionManagerCtrl
 * @{
 *
 * @addtogroup   SWC_VehicleMotionManager
 * @ingroup      LDC_VehicleMotionManagerCtrl
 * @{
 *
 * @addtogroup   SWM_VehicleMotionManager
 * @ingroup      SWC_VehicleMotionManager
 * @{
 *
 * @file  cunit_stubs.h
 * @brief 
 *
 ****************************************************************************/
#ifndef __C_CUNIT_STUBS_H__
#define __C_CUNIT_STUBS_H__
#include "Rte_StateEstimation.h"
#include <CUnit/CUnit.h>

typedef struct
{	struct
	{
		PassiveActive2_T par;
		Std_ReturnType ret;
	} Rte_ASREngineControlActive_ASREngineControlActive;

	struct
	{
		Percent8bit125NegOffset_T par;
		Std_ReturnType ret;
	} Rte_ActualEnginePercentTorque_ActualEnginePercentTorque;

	struct
	{
		Percent8bit125NegOffset_T par;
		Std_ReturnType ret;
	} Rte_ActualDrvlnRetdrPercentTorque_ActualDrvlnRetdrPercentTorque;

	struct
	{
		Torque16bit_T par;
		Std_ReturnType ret;
	} Rte_EngineReferenceTorque_EngineReferenceTorque;

	struct
	{
		TransmissionActualGearRatio_T par;
		Std_ReturnType ret;
	} Rte_TransmissionActualGearRatio_TransmissionActualGearRatio;

	struct
	{
		DisengageEngage_T par;
		Std_ReturnType ret;
	} Rte_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged;

	struct
	{
		RoadInclinationPerc_T par;
		Std_ReturnType ret;
	} Rte_RoadInclinationPerc_RoadInclinationPerc;

	struct
	{
		PassiveActive2_T par;
		Std_ReturnType ret;
	} Rte_ASRBrakeControlActive_ASRBrakeControlActive;

	struct
	{
		uint16 par;
		Std_ReturnType ret;
	} Rte_ActualEHPusherWheelAngle_ActuaEHPusherWheelAngle;

	struct
	{
		uint16 par;
		Std_ReturnType ret;
	} Rte_ActualEHTagWheelAngle_ActualEHTagWheelAngle;

	struct
	{
		ActualTagWheelAngle_T par;
		Std_ReturnType ret;
	} Rte_ActualTagWheelAngle_ActualTagWheelAngle;

	struct
	{
		AxleLoad_T par;
		Std_ReturnType ret;
	} Rte_DriveAxleLoad_AxleLoad;

	struct
	{
		PressureFactor5_T par;
		Std_ReturnType ret;
	} Rte_FrAxleLtWhlBrakeApplPrsHiRng_FrAxleLtWhlBrakeApplPrsHiRng;

	struct
	{
		PressureFactor5_T par;
		Std_ReturnType ret;
	} Rte_FrAxleRtWhlBrakeApplPrsHiRng_FrAxleRtWhlBrakeApplPrsHiRng;

	struct
	{
		AxleLoad_T par;
		Std_ReturnType ret;
	} Rte_FrontAxle1Load_AxleLoad;

	struct
	{
		AxleLoad_T par;
		Std_ReturnType ret;
	} Rte_FrontAxle2Load_AxleLoad;

	struct
	{
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_FrontAxleLeftWheelSpeed_FrontAxleLeftWheelSpeed;

	struct
	{
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_FrontAxleRightWheelSpeed_FrontAxleRightWheelSpeed;

	struct
	{
		RWhlAg_T par;
		Std_ReturnType ret;
	} Rte_FrontRoadWheelAngleEstimate_FrontRoadWheelAngleEstimate;

	struct
	{
		KFactor_T par;
		Std_ReturnType ret;
	} Rte_KFactor_KFactor;

	struct
	{
		LiftAxlePositionStatus_T par;
		Std_ReturnType ret;
	} Rte_LiftAxle1PositionStatus_LiftAxle1PositionStatus;

	struct
	{
		LiftAxlePositionStatus_T par;
		Std_ReturnType ret;
	} Rte_LiftAxle2PositionStatus_LiftAxle2PositionStatus;

	struct
	{
		Acceleration16bit_T par;
		Std_ReturnType ret;
	} Rte_LongitudinalAcceleration_LongitudinalAcceleration;

	struct
	{
		AxleLoad_T par;
		Std_ReturnType ret;
	} Rte_PusherAxleLoad_AxleLoad;

	struct
	{
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_RearAxleLeftWheelSpeed_RearAxleLeftWheelSpeed;

	struct
	{
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_RearAxleRightWheelSpeed_RearAxleRightWheelSpeed;

	struct
	{
		RearAxleSteeringFunctionStatus_T par;
		Std_ReturnType ret;
	} Rte_RearAxleSteeringFunctionStatus_RearAxleSteeringFunctionStatus;

	struct
	{
		PressureFactor5_T par;
		Std_ReturnType ret;
	} Rte_RrAxle1LtWhlBrakeApplPrsHiRng_RrAxle1LtWhlBrakeApplPrsHiRng;

	struct
	{
		PressureFactor5_T par;
		Std_ReturnType ret;
	} Rte_RrAxle1RtWhlBrakeApplPrsHiRng_RrAxle1RtWhlBrakeApplPrsHiRng;

	struct
	{
		PressureFactor5_T par;
		Std_ReturnType ret;
	} Rte_RrAxle2LtWhlBrakeApplPrsHiRng_RrAxle2LtWhlBrakeApplPrsHiRng;

	struct
	{
		PressureFactor5_T par;
		Std_ReturnType ret;
	} Rte_RrAxle2RtWhlBrakeApplPrsHiRng_RrAxle2RtWhlBrakeApplPrsHiRng;

	struct
	{
		PressureFactor5_T par;
		Std_ReturnType ret;
	} Rte_RrAxle3LtWhlBrakeApplPrsHiRng_RrAxle3LtWhlBrakeApplPrsHiRng;

	struct
	{
		PressureFactor5_T par;
		Std_ReturnType ret;
	} Rte_RrAxle3RtWhlBrakeApplPrsHiRng_RrAxle3RtWhlBrakeApplPrsHiRng;

	struct
	{
		AxleLoad_T par;
		Std_ReturnType ret;
	} Rte_SecondaryDriveAxleLoad_AxleLoad;

	struct
	{
		SteeringWheelAngle_T par;
		Std_ReturnType ret;
	} Rte_SteeringWheelAngle_SteeringWheelAngle;

	struct
	{
		AxleLoad_T par;
		Std_ReturnType ret;
	} Rte_TagAxleLoad_AxleLoad;

	struct
	{
		SpeedRpm16bitMinus4000_T par;
		Std_ReturnType ret;
	} Rte_TransmOutputShaftSpeedSigned_TransmOutputShaftSpeedSigned;

	struct
	{
		XPRsystemstate_T par;
		Std_ReturnType ret;
	} Rte_XPRsystemstate_XPRsystemstate;

	struct
	{
		uint16 par;
		Std_ReturnType ret;
	} Rte_YawRate_YawRate;

	struct
	{
		VehicleMode_T par;
		Std_ReturnType ret;
	} Rte_VehicleMode_VehicleMode;

	struct
	{
		Percent8bit125NegOffset_T par;
		Std_ReturnType ret;
	} Rte_ActualEngineRetarderPercentTrq_ActualEngineRetarderPercentTrq;

	struct
	{
		YawRateChassis_T par;
		Std_ReturnType ret;
	} Rte_AgrV_yawChassis_YawRateChassis;

	struct
	{
		YawAccChassis_T par;
		Std_ReturnType ret;
	} Rte_AgrA_yawChassis_YawAccChassis;

	struct
	{
		Speed_T par;
		Std_ReturnType ret;
	} Rte_V_spdXRefPoint_SpdXRefPoint;

	struct
	{
		Acceleration_T par;
		Std_ReturnType ret;
	} Rte_A_accXRefPoint_AccXRefPoint;

	struct
	{
		Acceleration_T par;
		Std_ReturnType ret;
	} Rte_A_accYRefPoint_AccYRefPoint;

	struct
	{
		Angle_T par;
		Std_ReturnType ret;
	} Rte_Ag_sideslipRefPoint_SideslipRefPoint;

	struct
	{
		Curvature_T par;
		Std_ReturnType ret;
	} Rte_Crvt_pathRefPoint_CrvtPathRefPoint;

	struct
	{
		CurvatureFac_T par;
		Std_ReturnType ret;
	} Rte_N_crvtFacRefPoint_CrvtFacRefPoint;

	struct
	{
		EquivalentRearAxlePos_T par;
		Std_ReturnType ret;
	} Rte_L_equivalentRearAxlePosition_EquivalentRearAxlePos;

	struct
	{
		MotionEstStatus_T par;
		Std_ReturnType ret;
	} Rte_E_motionEstStatus_MotionEstStatus;

	struct
	{
		Variance_T par;
		Std_ReturnType ret;
	} Rte_D_yawRateVari_YawRateVari;

	struct
	{
		Variance_T par;
		Std_ReturnType ret;
	} Rte_D_yawAccVari_YawAccVari;

	struct
	{
		Variance_T par;
		Std_ReturnType ret;
	} Rte_D_spdXVari_SpdXVari;

	struct
	{
		Variance_T par;
		Std_ReturnType ret;
	} Rte_D_spdYVari_SpdYVari;

	struct
	{
		Variance_T par;
		Std_ReturnType ret;
	} Rte_D_accXVari_AccXVari;

	struct
	{
		Variance_T par;
		Std_ReturnType ret;
	} Rte_D_accYVari_AccYVari;

	struct
	{
		Variance_T par;
		Std_ReturnType ret;
	} Rte_D_sideslipVari_SideslipVari;

	struct
	{
		Latency_T par;
		Std_ReturnType ret;
	} Rte_T_totalFilterLatencyEst_TotalFilterLatencyEst;

	struct
	{
		Angle_T par;
		Std_ReturnType ret;
	} Rte_Ag_chassisRollAngleEst_RollAngleChassisEst;

	struct
	{
		RollAngleEstQly_T par;
		Std_ReturnType ret;
	} Rte_E_chassisRollAngleEstQuality_RollAngleChassisEstQuality;

	struct
	{
		Acceleration_T par;
		Std_ReturnType ret;
	} Rte_A_spdXRateRefPoint_SpdXRateRefPoint;

	struct
	{
		Acceleration_T par;
		Std_ReturnType ret;
	} Rte_A_spdYRateRefPoint_SpdYRateRefPoint;

	struct
	{
		RoadWheelAngle_T2 par;
		Std_ReturnType ret;
	} Rte_Ag_roadWheelAngle_RoadWheelAngle;

	struct
	{
		Acceleration_T par;
		Std_ReturnType ret;
	} Rte_A_accYDueToBankAngle_AccYDueToBankAngle;

	struct
	{
		LongMotionDirection_sg_T par;
		Std_ReturnType ret;
	} Rte_LongMotionDirection_LongMotionDirection;

	struct
	{
		LongMotionDirectionQuality_T par;
		Std_ReturnType ret;
	} Rte_LongMotionDirectionQuality_LongMotionDirectionQuality;

	struct
	{
		LongMotionDirErrorSts_T par;
		Std_ReturnType ret;
	} Rte_LongMotionDirection_ErrorStatus_LongMotionDirection_ErrorStatus;

	struct
	{
		SteeringRatio_T par;
		Std_ReturnType ret;
	} Rte_D_nonlinearSteeringRatio_NonlinearSteeringRatio;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_spdXRefPointQly_SpdXRefPointQly;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_spdYRefPointQly_SpdYRefPointQly;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_accXRefPointQly_AccXRefPointQly;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_accYRefPointQly_AccYRefPointQly;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_yawRateRearAxleQly_YawRateRearAxleQly;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_yawAccRearAxleQly_YawAccRearAxleQly;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_sideslipRefPointQly_SideslipRefPointQly;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_roadWheelAngleQly_RoadWheelAngleQly;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_crvtPathRefPointQly_CrvtPathRefPointQly;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_equivalentRearAxlePositionQly_EquivalentRearAxlePositionQly;

	struct
	{
		Speed_T par;
		Std_ReturnType ret;
	} Rte_V_spdYRefPoint_SpdYRefPoint;

	struct
	{
		V_spdAtWhl_Ax1L_T par;
		Std_ReturnType ret;
	} Rte_V_spdAtWhl_Ax1L_V_spdAtWhl_Ax1L;

	struct
	{
		V_spdAtWhl_Ax1R_T par;
		Std_ReturnType ret;
	} Rte_V_spdAtWhl_Ax1R_V_spdAtWhl_Ax1R;

	struct
	{
		V_spdAtWhl_Ax2L_T par;
		Std_ReturnType ret;
	} Rte_V_spdAtWhl_Ax2L_V_spdAtWhl_Ax2L;

	struct
	{
		V_spdAtWhl_Ax2R_T par;
		Std_ReturnType ret;
	} Rte_V_spdAtWhl_Ax2R_V_spdAtWhl_Ax2R;

	struct
	{
		V_spdAtWhl_Ax3L_T par;
		Std_ReturnType ret;
	} Rte_V_spdAtWhl_Ax3L_V_spdAtWhl_Ax3L;

	struct
	{
		V_spdAtWhl_Ax3R_T par;
		Std_ReturnType ret;
	} Rte_V_spdAtWhl_Ax3R_V_spdAtWhl_Ax3R;

	struct
	{
		V_spdAtWhl_Ax4L_T par;
		Std_ReturnType ret;
	} Rte_V_spdAtWhl_Ax4L_V_spdAtWhl_Ax4L;

	struct
	{
		V_spdAtWhl_Ax4R_T par;
		Std_ReturnType ret;
	} Rte_V_spdAtWhl_Ax4R_V_spdAtWhl_Ax4R;

	struct
	{
		V_spdAtWhl_Ax5L_T par;
		Std_ReturnType ret;
	} Rte_V_spdAtWhl_Ax5L_V_spdAtWhl_Ax5L;

	struct
	{
		V_spdAtWhl_Ax5R_T par;
		Std_ReturnType ret;
	} Rte_V_spdAtWhl_Ax5R_V_spdAtWhl_Ax5R;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_spdAtWhlQly_Ax1L_E_spdAtWhlQly_Ax1L;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_spdAtWhlQly_Ax1R_E_spdAtWhlQly_Ax1R;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_spdAtWhlQly_Ax2L_E_spdAtWhlQly_Ax2L;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_spdAtWhlQly_Ax2R_E_spdAtWhlQly_Ax2R;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_spdAtWhlQly_Ax3L_E_spdAtWhlQly_Ax3L;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_spdAtWhlQly_Ax3R_E_spdAtWhlQly_Ax3R;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_spdAtWhlQly_Ax4L_E_spdAtWhlQly_Ax4L;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_spdAtWhlQly_Ax4R_E_spdAtWhlQly_Ax4R;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_spdAtWhlQly_Ax5R_E_spdAtWhlQly_Ax5R;

	struct
	{
		SignalQuality_T par;
		Std_ReturnType ret;
	} Rte_E_spdAtWhlQly_Ax5L_E_spdAtWhlQly_Ax5L;

} StubSignals_Type;

extern StubSignals_Type p;

typedef struct
{
		SEWS_D_precLongAccMeas_P10VW_T P10VW_D_precLongAccMeas;
		SEWS_SelfSteeredTagAxleThreshSpeed_P1AK9_T P1AK9_SelfSteeredTagAxleThreshSpeed;
		SEWS_D_lowSpdSnsrSelnLatAScaFac_X1C5B_T X1C5B_D_lowSpdSnsrSelnLatAScaFac;
		SEWS_D_FltHndlgIndirPrimSigFltScaFac_X1C6U_T X1C6U_D_FltHndlgIndirPrimSigFltScaFac;
		SEWS_ConfigAxle_4_axle_load_max_P1A8I_T P1A8I_ConfigAxle_4_axle_load_max;
		SEWS_D_precYawJerkInput_P10VT_T P10VT_D_precYawJerkInput;
		SEWS_ConfigAxle_4_p_thres_P1A8A_T P1A8A_ConfigAxle_4_p_thres;
		SEWS_D_FltHndlgPrimSigFltScaFac_X1C68_T X1C68_D_FltHndlgPrimSigFltScaFac;
		SEWS_ConfigAxle_1_axle_type_liftable_P1A59_T P1A59_ConfigAxle_1_axle_type_liftable;
		SEWS_ConfigAxle_2_wh_rollingcircu_P1A62_T P1A62_ConfigAxle_2_wh_rollingcircu;
		SEWS_ConfigAxle_4_axle_type_steered_P1A71_T P1A71_ConfigAxle_4_axle_type_steered;
		SEWS_T_interventionNoTrustTime_X1C60_T X1C60_T_interventionNoTrustTime;
		SEWS_SteeringRatio_P1BGV_T P1BGV_SteeringRatio;
		SEWS_VehicleType_P1L1L_T P1L1L_VehicleType;
		SEWS_ConfigAxle_2_axle_type_liftable_P1A6U_T P1A6U_ConfigAxle_2_axle_type_liftable;
		SEWS_ConfigAxle_3_wh_rollingcircu_P1A7N_T P1A7N_ConfigAxle_3_wh_rollingcircu;
		SEWS_Tq_minEngineWheelTorque_X1C8Y_T X1C8Y_Tq_minEngineWheelTorque;
		SEWS_D_lowSpdSnsrSelnWhlSpdScaFac_X1C5E_T X1C5E_D_lowSpdSnsrSelnWhlSpdScaFac;
		SEWS_D_normSlipStfnAxle5_P10WG_T P10WG_D_normSlipStfnAxle5;
		SEWS_T_absAsrTurnOffDly_X1DCK_T X1DCK_T_absAsrTurnOffDly;
		SEWS_M_Axle5SuspVertLoads_P10W2_a_T P10W2_M_Axle5SuspVertLoads;
		SEWS_ConfigAxle_2_axle_load_max_P1A7C_T P1A7C_ConfigAxle_2_axle_load_max;
		SEWS_M_Axle1SuspVertLoads_P10WU_a_T P10WU_M_Axle1SuspVertLoads;
		SEWS_ConfigAxle_5_axle_type_liftable_P1A8L_T P1A8L_ConfigAxle_5_axle_type_liftable;
		SEWS_Frq_lowSpdSnsrSelnTqFilFrq_X1C48_T X1C48_Frq_lowSpdSnsrSelnTqFilFrq;
		SEWS_ConfigAxle_1_p_thres_P1A6J_T P1A6J_ConfigAxle_1_p_thres;
		SEWS_ConfigAxle_1_axle_load_max_P1A6R_T P1A6R_ConfigAxle_1_axle_load_max;
		SEWS_D_normSlipStfnAxle2_P10WD_T P10WD_D_normSlipStfnAxle2;
		SEWS_ConfigAxle_5_axle_load_max_P1A83_T P1A83_ConfigAxle_5_axle_load_max;
		SEWS_FAxleContactPatchOutside2OutsideDist_P1KJ7_T P1KJ7_FAxleContactPatchOutside2OutsideDist;
		SEWS_RearAxleArrangement_P1CSG_T P1CSG_RearAxleArrangement;
		SEWS_ConfigAxle_3_brake_factor_P1A7Q_T P1A7Q_ConfigAxle_3_brake_factor;
		SEWS_T_absAsrRstDelayTime_X1DU3_T X1DU3_T_absAsrRstDelayTime;
		SEWS_VehicleTargetGeneratorSpeedLimits1_P1B8U_T P1B8U_VehicleTargetGeneratorSpeedLimits1;
		boolean X1BWH_YawRateMonitoringActivation;
		SEWS_Stfn_Axle5SuspVertStfns_P10W3_a_T P10W3_Stfn_Axle5SuspVertStfns;
		boolean X1C4J_B_enaSlipCmp;
		SEWS_Stfn_Axle2SuspVertStfns_P10WX_a_T P10WX_Stfn_Axle2SuspVertStfns;
		SEWS_D_precTrsmOutpShaftSpdMeas_X1C3K_T X1C3K_D_precTrsmOutpShaftSpdMeas;
		SEWS_ConfigAxle_3_axle_type_liftable_P1A7F_T P1A7F_ConfigAxle_3_axle_type_liftable;
		SEWS_ConfigAxle_5_axle_type_steered_P1A8M_T P1A8M_ConfigAxle_5_axle_type_steered;
		SEWS_V_mtnDetnThdSpd_X1C9S_T X1C9S_V_mtnDetnThdSpd;
		SEWS_A_mtnDetnThdLongAcc_X1DBJ_T X1DBJ_A_mtnDetnThdLongAcc;
		SEWS_D_precLongVelRateInit_X1C3E_T X1C3E_D_precLongVelRateInit;
		SEWS_BrandType_P1AFC_T P1AFC_BrandType;
		SEWS_Frq_lowSpdSnsrSelnSpdFilFrq_X1C49_T X1C49_Frq_lowSpdSnsrSelnSpdFilFrq;
		SEWS_SteeringRatioRight2_P1BGZ_T P1BGZ_SteeringRatioRight2;
		boolean X1DCG_B_enaAbsAsrDetn;
		SEWS_V_lowSpdSnsrSelnSpdThldUp_P10V2_T P10V2_V_lowSpdSnsrSelnSpdThldUp;
		SEWS_D_normSlipStfnAxle3_P10WE_T P10WE_D_normSlipStfnAxle3;
		SEWS_DistRA1ToRA2_P1CNH_T P1CNH_DistRA1ToRA2;
		SEWS_D_lowSpdSnsrSelnYawRateScaFac_X1C5C_T X1C5C_D_lowSpdSnsrSelnYawRateScaFac;
		SEWS_D_absTracCompLgtAScaFac_X1C63_T X1C63_D_absTracCompLgtAScaFac;
		SEWS_D_precLatJerkDueToBankAngleInput_P10VU_T P10VU_D_precLatJerkDueToBankAngleInput;
		SEWS_D_FltHndlgIndirAltvSigFltScaFac_X1C6V_T X1C6V_D_FltHndlgIndirAltvSigFltScaFac;
		SEWS_ConfigAxle_2_axle_load_min_P1A7B_T P1A7B_ConfigAxle_2_axle_load_min;
		SEWS_M_Axle4SuspVertLoads_P10W0_a_T P10W0_M_Axle4SuspVertLoads;
		SEWS_L_trackWidthDrivenAxle_X1C3A_T X1C3A_L_trackWidthDrivenAxle;
		SEWS_ConfigAxle_1_axle_type_steered_P1A6A_T P1A6A_ConfigAxle_1_axle_type_steered;
		SEWS_ConfigAxle_2_brake_factor_P1A65_T P1A65_ConfigAxle_2_brake_factor;
		SEWS_D_maxWheelSpeedTrustFac_vec_X1C69_a_T X1C69_D_maxWheelSpeedTrustFac_vec;
		SEWS_Tq_lowSpdSnsrSelnTqThldUp_X1C46_T X1C46_Tq_lowSpdSnsrSelnTqThldUp;
		SEWS_ConfigAxle_3_axle_load_min_P1A7W_T P1A7W_ConfigAxle_3_axle_load_min;
		SEWS_SteeringRatioLeft1_P1BGW_T P1BGW_SteeringRatioLeft1;
		SEWS_D_precWhlSpdMeas_X1C5P_T X1C5P_D_precWhlSpdMeas;
		SEWS_ConfigAxle_2_axle_type_steered_P1A6V_T P1A6V_ConfigAxle_2_axle_type_steered;
		SEWS_T_zeroSpdFltrTurnOffDly_X1C5W_T X1C5W_T_zeroSpdFltrTurnOffDly;
		SEWS_D_wheelSpeedTrustFac_vec_X1C8Z_a_T X1C8Z_D_wheelSpeedTrustFac_vec;
		SEWS_DistRA2ToRA3_P1CNJ_T P1CNJ_DistRA2ToRA3;
		SEWS_L_imuToFrontAxle_P10WH_T P10WH_L_imuToFrontAxle;
		SEWS_Stfn_Axle4SuspVertStfns_P10W1_a_T P10W1_Stfn_Axle4SuspVertStfns;
		SEWS_ConfigAxle_4_wh_rollingcircu_P1A78_T P1A78_ConfigAxle_4_wh_rollingcircu;
		SEWS_L_maxCogHeightFullyLaden_P10WS_T P10WS_L_maxCogHeightFullyLaden;
		SEWS_E_EbsSwPackage_P1K5K_T P1K5K_E_EbsSwPackage;
		boolean X1C4U_B_enaLowSpdSnsrSeln;
		SEWS_Stfn_Axle1SuspVertStfns_P10WV_a_T P10WV_Stfn_Axle1SuspVertStfns;
		SEWS_Tq_lowSpdSnsrSelnTqThldLo_X1C47_T X1C47_Tq_lowSpdSnsrSelnTqThldLo;
		SEWS_ConfigAxle_3_axle_load_max_P1A7X_T P1A7X_ConfigAxle_3_axle_load_max;
		SEWS_ConfigAxle_1_brake_factor_P1A6K_T P1A6K_ConfigAxle_1_brake_factor;
		SEWS_T_mtnLowConfTolrTi_X1DCF_T X1DCF_T_mtnLowConfTolrTi;
		SEWS_ConfigAxle_1_axle_load_min_P1A6Q_T P1A6Q_ConfigAxle_1_axle_load_min;
		SEWS_FrontAxleArrangement_P1CSH_T P1CSH_FrontAxleArrangement;
		SEWS_ConfigAxle_5_axle_load_min_P1A82_T P1A82_ConfigAxle_5_axle_load_min;
		SEWS_D_precLatAccDueToBankAngleInit_X1DBH_T X1DBH_D_precLatAccDueToBankAngleInit;
		SEWS_D_precLatAccMeas_P10VX_T P10VX_D_precLatAccMeas;
		SEWS_D_FltHndlgAltvSigFltScaFac_X1C6T_T X1C6T_D_FltHndlgAltvSigFltScaFac;
		SEWS_E_BusAxleType_P11DU_T P11DU_E_BusAxleType;
		SEWS_VehicleTargetGeneratorSpeedLimits2_P1B8V_T P1B8V_VehicleTargetGeneratorSpeedLimits2;
		SEWS_D_absTracCompLongJerkScaFac_X1DBQ_T X1DBQ_D_absTracCompLongJerkScaFac;
		SEWS_D_lowSpdSnsrSelnLgtAScaFac_X1C5A_T X1C5A_D_lowSpdSnsrSelnLgtAScaFac;
		SEWS_T_interventionRampUpTime_X1C61_T X1C61_T_interventionRampUpTime;
		SEWS_D_precLongJerkInput_P10VS_T P10VS_D_precLongJerkInput;
		SEWS_ConfigAxle_4_axle_load_min_P1A8H_T P1A8H_ConfigAxle_4_axle_load_min;
		SEWS_DistFA1ToFA2_P1KME_T P1KME_DistFA1ToFA2;
		SEWS_D_absTracCompLatAScaFac_X1DBO_T X1DBO_D_absTracCompLatAScaFac;
		SEWS_D_lowSpdSnsrSelnLgtJerkScaFacSpd_X1C5T_T X1C5T_D_lowSpdSnsrSelnLgtJerkScaFacSpd;
		SEWS_M_Axle3SuspVertLoads_P10WY_a_T P10WY_M_Axle3SuspVertLoads;
		SEWS_ConfigAxle_4_brake_factor_P1A8B_T P1A8B_ConfigAxle_4_brake_factor;
		boolean X1C8W_B_enaWheelDeselection;
		SEWS_T_absAsrDetnDelayTime_X1DU0_T X1DU0_T_absAsrDetnDelayTime;
		SEWS_ConfigAxle_3_axle_type_steered_P1A7G_T P1A7G_ConfigAxle_3_axle_type_steered;
		SEWS_D_precYawRateInit_X1C3F_T X1C3F_D_precYawRateInit;
		SEWS_ConfigAxle_1_wh_rollingcircu_P1A6H_T P1A6H_ConfigAxle_1_wh_rollingcircu;
		SEWS_ConfigAxle_4_axle_type_liftable_P1A70_T P1A70_ConfigAxle_4_axle_type_liftable;
		SEWS_A_whlRateAbsAsrDetnThd_X1DCH_T X1DCH_A_whlRateAbsAsrDetnThd;
		SEWS_ConfigAxle_5_p_thres_P1A8V_T P1A8V_ConfigAxle_5_p_thres;
		SEWS_ConfigAxle_3_p_thres_P1A7P_T P1A7P_ConfigAxle_3_p_thres;
		SEWS_NetworkArchitecture_P1RPH_T P1RPH_NetworkArchitecture;
		SEWS_D_precYawRateMeas_P10VY_T P10VY_D_precYawRateMeas;
		SEWS_D_lowSpdSnsrSelnTrsmSpdScaFac_X1C5D_T X1C5D_D_lowSpdSnsrSelnTrsmSpdScaFac;
		SEWS_TagAxleFeatures_P1CSI_T P1CSI_TagAxleFeatures;
		SEWS_D_normSlipStfnAxle4_P10WF_T P10WF_D_normSlipStfnAxle4;
		boolean X1C62_B_enaTracComp;
		SEWS_D_absTracCompYawRateScaFac_X1DBP_T X1DBP_D_absTracCompYawRateScaFac;
		SEWS_V_maxWheelSpeedTrustBreakPoints_vec_X1C7C_a_T X1C7C_V_maxWheelSpeedTrustBreakPoints_vec;
		SEWS_Frq_lowSpdSnsrSelnSpdFilFrq_X1C5U_T X1C5U_Frq_lowSpdSnsrSelnSpdFilFrq;
		SEWS_Stfn_Axle3SuspVertStfns_P10WZ_a_T P10WZ_Stfn_Axle3SuspVertStfns;
		SEWS_L_trackWidthNonDrivenAxle_X1C29_T X1C29_L_trackWidthNonDrivenAxle;
		SEWS_Tq_minTotalBrakeTorque_X1C8X_T X1C8X_Tq_minTotalBrakeTorque;
		SEWS_D_precYawAccInit_X1C3G_T X1C3G_D_precYawAccInit;
		SEWS_ConfigAxle_2_p_thres_P1A64_T P1A64_ConfigAxle_2_p_thres;
		SEWS_Radar2FrontAxleDist_P1E5Z_T P1E5Z_Radar2FrontAxleDist;
		SEWS_ConfigAxle_5_brake_factor_P1A8W_T P1A8W_ConfigAxle_5_brake_factor;
		SEWS_D_normSlipStfnAxle1_P10WC_T P10WC_D_normSlipStfnAxle1;
		SEWS_Frq_whlRateFilFrq_X1DCI_T X1DCI_Frq_whlRateFilFrq;
		SEWS_D_lowSpdSnsrSelnLgtJerkScaFacTrq_X1C5Q_T X1C5Q_D_lowSpdSnsrSelnLgtJerkScaFacTrq;
		SEWS_L_minCogHeightUnladen_P10WR_T P10WR_L_minCogHeightUnladen;
		SEWS_V_speedDifferenceBreakPoints_vec_X1C80_a_T X1C80_V_speedDifferenceBreakPoints_vec;
		SEWS_EquivalentWheelbaseTurning_P1IJ3_T P1IJ3_EquivalentWheelbaseTurning;
		SEWS_A_whlRateAbsAsrRstThd_X1DCM_T X1DCM_A_whlRateAbsAsrRstThd;
		SEWS_D_precLongVelInit_X1C3D_T X1C3D_D_precLongVelInit;
		SEWS_SelfSteeredTagAxleSpeedHysteresis_P1AT2_T P1AT2_SelfSteeredTagAxleSpeedHysteresis;
		SEWS_AgV_maxPitchRate_P10WT_T P10WT_AgV_maxPitchRate;
		SEWS_M_Axle2SuspVertLoads_P10WW_a_T P10WW_M_Axle2SuspVertLoads;
		SEWS_SteeringRatioLeft2_P1BGX_T P1BGX_SteeringRatioLeft2;
		SEWS_V_mtnDetnHysSpd_X1C9T_T X1C9T_V_mtnDetnHysSpd;
		boolean X1C6Z_B_enaAbsComp;
		SEWS_SteeringRatioRight1_P1BGY_T P1BGY_SteeringRatioRight1;
		SEWS_V_lowSpdSnsrSelnSpdThldLo_P10V1_T P10V1_V_lowSpdSnsrSelnSpdThldLo;
		SEWS_ConfigAxle_5_wh_rollingcircu_P1A8T_T P1A8T_ConfigAxle_5_wh_rollingcircu;
		boolean P1A0N_B_EspNotAvailable;
		SEWS_WheelBase_P1AZQ_T P1AZQ_WheelBase;
		SEWS_VehicleWidth_mm_P1E50_T P1E50_VehicleWidth_mm;
		SEWS_NoOfPulsesPerRevolution_P1M6I_T P1M6I_NoOfPulsesPerRevolution;
		boolean P1C54_FactoryModeActive;
} StubConfig_Type;

StubConfig_Type c = {
	0, /*P10VW_D_precLongAccMeas*/
	0, /*P1AK9_SelfSteeredTagAxleThreshSpeed*/
	0, /*X1C5B_D_lowSpdSnsrSelnLatAScaFac*/
	0, /*X1C6U_D_FltHndlgIndirPrimSigFltScaFac*/
	0, /*P1A8I_ConfigAxle_4_axle_load_max*/
	0, /*P10VT_D_precYawJerkInput*/
	0, /*P1A8A_ConfigAxle_4_p_thres*/
	0, /*X1C68_D_FltHndlgPrimSigFltScaFac*/
	0, /*P1A59_ConfigAxle_1_axle_type_liftable*/
	0, /*P1A62_ConfigAxle_2_wh_rollingcircu*/
	0, /*P1A71_ConfigAxle_4_axle_type_steered*/
	0, /*X1C60_T_interventionNoTrustTime*/
	0, /*P1BGV_SteeringRatio*/
	0, /*P1L1L_VehicleType*/
	0, /*P1A6U_ConfigAxle_2_axle_type_liftable*/
	0, /*P1A7N_ConfigAxle_3_wh_rollingcircu*/
	0, /*X1C8Y_Tq_minEngineWheelTorque*/
	0, /*X1C5E_D_lowSpdSnsrSelnWhlSpdScaFac*/
	0, /*P10WG_D_normSlipStfnAxle5*/
	0, /*X1DCK_T_absAsrTurnOffDly*/
	{0, 0}, /*P10W2_M_Axle5SuspVertLoads*/
	0, /*P1A7C_ConfigAxle_2_axle_load_max*/
	{0, 0}, /*P10WU_M_Axle1SuspVertLoads*/
	0, /*P1A8L_ConfigAxle_5_axle_type_liftable*/
	0, /*X1C48_Frq_lowSpdSnsrSelnTqFilFrq*/
	0, /*P1A6J_ConfigAxle_1_p_thres*/
	0, /*P1A6R_ConfigAxle_1_axle_load_max*/
	0, /*P10WD_D_normSlipStfnAxle2*/
	0, /*P1A83_ConfigAxle_5_axle_load_max*/
	0, /*P1KJ7_FAxleContactPatchOutside2OutsideDist*/
	0, /*P1CSG_RearAxleArrangement*/
	0, /*P1A7Q_ConfigAxle_3_brake_factor*/
	0, /*X1DU3_T_absAsrRstDelayTime*/
	0, /*P1B8U_VehicleTargetGeneratorSpeedLimits1*/
	0, /*X1BWH_YawRateMonitoringActivation*/
	{0, 0}, /*P10W3_Stfn_Axle5SuspVertStfns*/
	0, /*X1C4J_B_enaSlipCmp*/
	{0, 0}, /*P10WX_Stfn_Axle2SuspVertStfns*/
	0, /*X1C3K_D_precTrsmOutpShaftSpdMeas*/
	0, /*P1A7F_ConfigAxle_3_axle_type_liftable*/
	0, /*P1A8M_ConfigAxle_5_axle_type_steered*/
	0, /*X1C9S_V_mtnDetnThdSpd*/
	0, /*X1DBJ_A_mtnDetnThdLongAcc*/
	0, /*X1C3E_D_precLongVelRateInit*/
	0, /*P1AFC_BrandType*/
	0, /*X1C49_Frq_lowSpdSnsrSelnSpdFilFrq*/
	0, /*P1BGZ_SteeringRatioRight2*/
	0, /*X1DCG_B_enaAbsAsrDetn*/
	0, /*P10V2_V_lowSpdSnsrSelnSpdThldUp*/
	0, /*P10WE_D_normSlipStfnAxle3*/
	0, /*P1CNH_DistRA1ToRA2*/
	0, /*X1C5C_D_lowSpdSnsrSelnYawRateScaFac*/
	0, /*X1C63_D_absTracCompLgtAScaFac*/
	0, /*P10VU_D_precLatJerkDueToBankAngleInput*/
	0, /*X1C6V_D_FltHndlgIndirAltvSigFltScaFac*/
	0, /*P1A7B_ConfigAxle_2_axle_load_min*/
	{0, 0}, /*P10W0_M_Axle4SuspVertLoads*/
	0, /*X1C3A_L_trackWidthDrivenAxle*/
	0, /*P1A6A_ConfigAxle_1_axle_type_steered*/
	0, /*P1A65_ConfigAxle_2_brake_factor*/
	{0, 0, 0, 0, 0}, /*X1C69_D_maxWheelSpeedTrustFac_vec*/
	0, /*X1C46_Tq_lowSpdSnsrSelnTqThldUp*/
	0, /*P1A7W_ConfigAxle_3_axle_load_min*/
	0, /*P1BGW_SteeringRatioLeft1*/
	0, /*X1C5P_D_precWhlSpdMeas*/
	0, /*P1A6V_ConfigAxle_2_axle_type_steered*/
	0, /*X1C5W_T_zeroSpdFltrTurnOffDly*/
	{0, 0, 0, 0, 0}, /*X1C8Z_D_wheelSpeedTrustFac_vec*/
	0, /*P1CNJ_DistRA2ToRA3*/
	0, /*P10WH_L_imuToFrontAxle*/
	{0, 0}, /*P10W1_Stfn_Axle4SuspVertStfns*/
	0, /*P1A78_ConfigAxle_4_wh_rollingcircu*/
	0, /*P10WS_L_maxCogHeightFullyLaden*/
	0, /*P1K5K_E_EbsSwPackage*/
	0, /*X1C4U_B_enaLowSpdSnsrSeln*/
	{0, 0}, /*P10WV_Stfn_Axle1SuspVertStfns*/
	0, /*X1C47_Tq_lowSpdSnsrSelnTqThldLo*/
	0, /*P1A7X_ConfigAxle_3_axle_load_max*/
	0, /*P1A6K_ConfigAxle_1_brake_factor*/
	0, /*X1DCF_T_mtnLowConfTolrTi*/
	0, /*P1A6Q_ConfigAxle_1_axle_load_min*/
	0, /*P1CSH_FrontAxleArrangement*/
	0, /*P1A82_ConfigAxle_5_axle_load_min*/
	0, /*X1DBH_D_precLatAccDueToBankAngleInit*/
	0, /*P10VX_D_precLatAccMeas*/
	0, /*X1C6T_D_FltHndlgAltvSigFltScaFac*/
	0, /*P11DU_E_BusAxleType*/
	0, /*P1B8V_VehicleTargetGeneratorSpeedLimits2*/
	0, /*X1DBQ_D_absTracCompLongJerkScaFac*/
	0, /*X1C5A_D_lowSpdSnsrSelnLgtAScaFac*/
	0, /*X1C61_T_interventionRampUpTime*/
	0, /*P10VS_D_precLongJerkInput*/
	0, /*P1A8H_ConfigAxle_4_axle_load_min*/
	0, /*P1KME_DistFA1ToFA2*/
	0, /*X1DBO_D_absTracCompLatAScaFac*/
	0, /*X1C5T_D_lowSpdSnsrSelnLgtJerkScaFacSpd*/
	{0, 0}, /*P10WY_M_Axle3SuspVertLoads*/
	0, /*P1A8B_ConfigAxle_4_brake_factor*/
	0, /*X1C8W_B_enaWheelDeselection*/
	0, /*X1DU0_T_absAsrDetnDelayTime*/
	0, /*P1A7G_ConfigAxle_3_axle_type_steered*/
	0, /*X1C3F_D_precYawRateInit*/
	0, /*P1A6H_ConfigAxle_1_wh_rollingcircu*/
	0, /*P1A70_ConfigAxle_4_axle_type_liftable*/
	0, /*X1DCH_A_whlRateAbsAsrDetnThd*/
	0, /*P1A8V_ConfigAxle_5_p_thres*/
	0, /*P1A7P_ConfigAxle_3_p_thres*/
	0, /*P1RPH_NetworkArchitecture*/
	0, /*P10VY_D_precYawRateMeas*/
	0, /*X1C5D_D_lowSpdSnsrSelnTrsmSpdScaFac*/
	0, /*P1CSI_TagAxleFeatures*/
	0, /*P10WF_D_normSlipStfnAxle4*/
	0, /*X1C62_B_enaTracComp*/
	0, /*X1DBP_D_absTracCompYawRateScaFac*/
	{0, 0, 0, 0, 0}, /*X1C7C_V_maxWheelSpeedTrustBreakPoints_vec*/
	0, /*X1C5U_Frq_lowSpdSnsrSelnSpdFilFrq*/
	{0, 0}, /*P10WZ_Stfn_Axle3SuspVertStfns*/
	0, /*X1C29_L_trackWidthNonDrivenAxle*/
	0, /*X1C8X_Tq_minTotalBrakeTorque*/
	0, /*X1C3G_D_precYawAccInit*/
	0, /*P1A64_ConfigAxle_2_p_thres*/
	0, /*P1E5Z_Radar2FrontAxleDist*/
	0, /*P1A8W_ConfigAxle_5_brake_factor*/
	0, /*P10WC_D_normSlipStfnAxle1*/
	0, /*X1DCI_Frq_whlRateFilFrq*/
	0, /*X1C5Q_D_lowSpdSnsrSelnLgtJerkScaFacTrq*/
	0, /*P10WR_L_minCogHeightUnladen*/
	{0, 0, 0, 0, 0}, /*X1C80_V_speedDifferenceBreakPoints_vec*/
	0, /*P1IJ3_EquivalentWheelbaseTurning*/
	0, /*X1DCM_A_whlRateAbsAsrRstThd*/
	0, /*X1C3D_D_precLongVelInit*/
	0, /*P1AT2_SelfSteeredTagAxleSpeedHysteresis*/
	0, /*P10WT_AgV_maxPitchRate*/
	{0, 0}, /*P10WW_M_Axle2SuspVertLoads*/
	0, /*P1BGX_SteeringRatioLeft2*/
	0, /*X1C9T_V_mtnDetnHysSpd*/
	0, /*X1C6Z_B_enaAbsComp*/
	0, /*P1BGY_SteeringRatioRight1*/
	0, /*P10V1_V_lowSpdSnsrSelnSpdThldLo*/
	0, /*P1A8T_ConfigAxle_5_wh_rollingcircu*/
	0, /*P1A0N_B_EspNotAvailable*/
	0, /*P1AZQ_WheelBase*/
	0, /*P1E50_VehicleWidth_mm*/
	0, /*P1M6I_NoOfPulsesPerRevolution*/
	0, /*P1C54_FactoryModeActive*/
};

void stubs_set_ASREngineControlActive_ASREngineControlActive(PassiveActive2_T par);
void stubs_set_ActualEnginePercentTorque_ActualEnginePercentTorque(Percent8bit125NegOffset_T par);
void stubs_set_ActualDrvlnRetdrPercentTorque_ActualDrvlnRetdrPercentTorque(Percent8bit125NegOffset_T par);
void stubs_set_EngineReferenceTorque_EngineReferenceTorque(Torque16bit_T par);
void stubs_set_TransmissionActualGearRatio_TransmissionActualGearRatio(TransmissionActualGearRatio_T par);
void stubs_set_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged(DisengageEngage_T par);
void stubs_set_RoadInclinationPerc_RoadInclinationPerc(RoadInclinationPerc_T par);
void stubs_set_ASRBrakeControlActive_ASRBrakeControlActive(PassiveActive2_T par);
void stubs_set_ActualEHPusherWheelAngle_ActuaEHPusherWheelAngle(uint16 par);
void stubs_set_ActualEHTagWheelAngle_ActualEHTagWheelAngle(uint16 par);
void stubs_set_ActualTagWheelAngle_ActualTagWheelAngle(ActualTagWheelAngle_T par);
void stubs_set_DriveAxleLoad_AxleLoad(AxleLoad_T par);
void stubs_set_FrAxleLtWhlBrakeApplPrsHiRng_FrAxleLtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_FrAxleRtWhlBrakeApplPrsHiRng_FrAxleRtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_FrontAxle1Load_AxleLoad(AxleLoad_T par);
void stubs_set_FrontAxle2Load_AxleLoad(AxleLoad_T par);
void stubs_set_FrontAxleLeftWheelSpeed_FrontAxleLeftWheelSpeed(Speed16bit_T par);
void stubs_set_FrontAxleRightWheelSpeed_FrontAxleRightWheelSpeed(Speed16bit_T par);
void stubs_set_FrontRoadWheelAngleEstimate_FrontRoadWheelAngleEstimate(RWhlAg_T par);
void stubs_set_KFactor_KFactor(KFactor_T par);
void stubs_set_LiftAxle1PositionStatus_LiftAxle1PositionStatus(LiftAxlePositionStatus_T par);
void stubs_set_LiftAxle2PositionStatus_LiftAxle2PositionStatus(LiftAxlePositionStatus_T par);
void stubs_set_LongitudinalAcceleration_LongitudinalAcceleration(Acceleration16bit_T par);
void stubs_set_PusherAxleLoad_AxleLoad(AxleLoad_T par);
void stubs_set_RearAxleLeftWheelSpeed_RearAxleLeftWheelSpeed(Speed16bit_T par);
void stubs_set_RearAxleRightWheelSpeed_RearAxleRightWheelSpeed(Speed16bit_T par);
void stubs_set_RearAxleSteeringFunctionStatus_RearAxleSteeringFunctionStatus(RearAxleSteeringFunctionStatus_T par);
void stubs_set_RrAxle1LtWhlBrakeApplPrsHiRng_RrAxle1LtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_RrAxle1RtWhlBrakeApplPrsHiRng_RrAxle1RtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_RrAxle2LtWhlBrakeApplPrsHiRng_RrAxle2LtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_RrAxle2RtWhlBrakeApplPrsHiRng_RrAxle2RtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_RrAxle3LtWhlBrakeApplPrsHiRng_RrAxle3LtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_RrAxle3RtWhlBrakeApplPrsHiRng_RrAxle3RtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_SecondaryDriveAxleLoad_AxleLoad(AxleLoad_T par);
void stubs_set_SteeringWheelAngle_SteeringWheelAngle(SteeringWheelAngle_T par);
void stubs_set_TagAxleLoad_AxleLoad(AxleLoad_T par);
void stubs_set_TransmOutputShaftSpeedSigned_TransmOutputShaftSpeedSigned(SpeedRpm16bitMinus4000_T par);
void stubs_set_XPRsystemstate_XPRsystemstate(XPRsystemstate_T par);
void stubs_set_YawRate_YawRate(uint16 par);
void stubs_set_VehicleMode_VehicleMode(VehicleMode_T par);
void stubs_set_ActualEngineRetarderPercentTrq_ActualEngineRetarderPercentTrq(Percent8bit125NegOffset_T par);
#define stubs_check_AgrV_yawChassis_YawRateChassis(expected) _stubs_check_AgrV_yawChassis_YawRateChassis(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_AgrV_yawChassis_YawRateChassis(YawRateChassis_T* expected, const char *file, const char *function, const int line);

#define stubs_check_AgrA_yawChassis_YawAccChassis(expected) _stubs_check_AgrA_yawChassis_YawAccChassis(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_AgrA_yawChassis_YawAccChassis(YawAccChassis_T* expected, const char *file, const char *function, const int line);

#define stubs_check_V_spdXRefPoint_SpdXRefPoint(expected) _stubs_check_V_spdXRefPoint_SpdXRefPoint(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_V_spdXRefPoint_SpdXRefPoint(Speed_T* expected, const char *file, const char *function, const int line);

#define stubs_check_A_accXRefPoint_AccXRefPoint(expected) _stubs_check_A_accXRefPoint_AccXRefPoint(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_A_accXRefPoint_AccXRefPoint(Acceleration_T* expected, const char *file, const char *function, const int line);

#define stubs_check_A_accYRefPoint_AccYRefPoint(expected) _stubs_check_A_accYRefPoint_AccYRefPoint(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_A_accYRefPoint_AccYRefPoint(Acceleration_T* expected, const char *file, const char *function, const int line);

#define stubs_check_Ag_sideslipRefPoint_SideslipRefPoint(expected) _stubs_check_Ag_sideslipRefPoint_SideslipRefPoint(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_Ag_sideslipRefPoint_SideslipRefPoint(Angle_T* expected, const char *file, const char *function, const int line);

#define stubs_check_Crvt_pathRefPoint_CrvtPathRefPoint(expected) _stubs_check_Crvt_pathRefPoint_CrvtPathRefPoint(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_Crvt_pathRefPoint_CrvtPathRefPoint(Curvature_T* expected, const char *file, const char *function, const int line);

#define stubs_check_N_crvtFacRefPoint_CrvtFacRefPoint(expected) _stubs_check_N_crvtFacRefPoint_CrvtFacRefPoint(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_N_crvtFacRefPoint_CrvtFacRefPoint(CurvatureFac_T* expected, const char *file, const char *function, const int line);

#define stubs_check_L_equivalentRearAxlePosition_EquivalentRearAxlePos(expected) _stubs_check_L_equivalentRearAxlePosition_EquivalentRearAxlePos(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_L_equivalentRearAxlePosition_EquivalentRearAxlePos(EquivalentRearAxlePos_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_motionEstStatus_MotionEstStatus(expected) _stubs_check_E_motionEstStatus_MotionEstStatus(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_motionEstStatus_MotionEstStatus(MotionEstStatus_T* expected, const char *file, const char *function, const int line);

#define stubs_check_D_yawRateVari_YawRateVari(expected) _stubs_check_D_yawRateVari_YawRateVari(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_D_yawRateVari_YawRateVari(Variance_T* expected, const char *file, const char *function, const int line);

#define stubs_check_D_yawAccVari_YawAccVari(expected) _stubs_check_D_yawAccVari_YawAccVari(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_D_yawAccVari_YawAccVari(Variance_T* expected, const char *file, const char *function, const int line);

#define stubs_check_D_spdXVari_SpdXVari(expected) _stubs_check_D_spdXVari_SpdXVari(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_D_spdXVari_SpdXVari(Variance_T* expected, const char *file, const char *function, const int line);

#define stubs_check_D_spdYVari_SpdYVari(expected) _stubs_check_D_spdYVari_SpdYVari(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_D_spdYVari_SpdYVari(Variance_T* expected, const char *file, const char *function, const int line);

#define stubs_check_D_accXVari_AccXVari(expected) _stubs_check_D_accXVari_AccXVari(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_D_accXVari_AccXVari(Variance_T* expected, const char *file, const char *function, const int line);

#define stubs_check_D_accYVari_AccYVari(expected) _stubs_check_D_accYVari_AccYVari(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_D_accYVari_AccYVari(Variance_T* expected, const char *file, const char *function, const int line);

#define stubs_check_D_sideslipVari_SideslipVari(expected) _stubs_check_D_sideslipVari_SideslipVari(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_D_sideslipVari_SideslipVari(Variance_T* expected, const char *file, const char *function, const int line);

#define stubs_check_T_totalFilterLatencyEst_TotalFilterLatencyEst(expected) _stubs_check_T_totalFilterLatencyEst_TotalFilterLatencyEst(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_T_totalFilterLatencyEst_TotalFilterLatencyEst(Latency_T* expected, const char *file, const char *function, const int line);

#define stubs_check_Ag_chassisRollAngleEst_RollAngleChassisEst(expected) _stubs_check_Ag_chassisRollAngleEst_RollAngleChassisEst(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_Ag_chassisRollAngleEst_RollAngleChassisEst(Angle_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_chassisRollAngleEstQuality_RollAngleChassisEstQuality(expected) _stubs_check_E_chassisRollAngleEstQuality_RollAngleChassisEstQuality(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_chassisRollAngleEstQuality_RollAngleChassisEstQuality(RollAngleEstQly_T* expected, const char *file, const char *function, const int line);

#define stubs_check_A_spdXRateRefPoint_SpdXRateRefPoint(expected) _stubs_check_A_spdXRateRefPoint_SpdXRateRefPoint(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_A_spdXRateRefPoint_SpdXRateRefPoint(Acceleration_T* expected, const char *file, const char *function, const int line);

#define stubs_check_A_spdYRateRefPoint_SpdYRateRefPoint(expected) _stubs_check_A_spdYRateRefPoint_SpdYRateRefPoint(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_A_spdYRateRefPoint_SpdYRateRefPoint(Acceleration_T* expected, const char *file, const char *function, const int line);

#define stubs_check_Ag_roadWheelAngle_RoadWheelAngle(expected) _stubs_check_Ag_roadWheelAngle_RoadWheelAngle(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_Ag_roadWheelAngle_RoadWheelAngle(RoadWheelAngle_T2* expected, const char *file, const char *function, const int line);

#define stubs_check_A_accYDueToBankAngle_AccYDueToBankAngle(expected) _stubs_check_A_accYDueToBankAngle_AccYDueToBankAngle(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_A_accYDueToBankAngle_AccYDueToBankAngle(Acceleration_T* expected, const char *file, const char *function, const int line);

#define stubs_check_LongMotionDirection_LongMotionDirection(expected) _stubs_check_LongMotionDirection_LongMotionDirection(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_LongMotionDirection_LongMotionDirection(LongMotionDirection_sg_T* expected, const char *file, const char *function, const int line);

#define stubs_check_LongMotionDirectionQuality_LongMotionDirectionQuality(expected) _stubs_check_LongMotionDirectionQuality_LongMotionDirectionQuality(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_LongMotionDirectionQuality_LongMotionDirectionQuality(LongMotionDirectionQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_LongMotionDirection_ErrorStatus_LongMotionDirection_ErrorStatus(expected) _stubs_check_LongMotionDirection_ErrorStatus_LongMotionDirection_ErrorStatus(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_LongMotionDirection_ErrorStatus_LongMotionDirection_ErrorStatus(LongMotionDirErrorSts_T* expected, const char *file, const char *function, const int line);

#define stubs_check_D_nonlinearSteeringRatio_NonlinearSteeringRatio(expected) _stubs_check_D_nonlinearSteeringRatio_NonlinearSteeringRatio(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_D_nonlinearSteeringRatio_NonlinearSteeringRatio(SteeringRatio_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_spdXRefPointQly_SpdXRefPointQly(expected) _stubs_check_E_spdXRefPointQly_SpdXRefPointQly(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_spdXRefPointQly_SpdXRefPointQly(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_spdYRefPointQly_SpdYRefPointQly(expected) _stubs_check_E_spdYRefPointQly_SpdYRefPointQly(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_spdYRefPointQly_SpdYRefPointQly(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_accXRefPointQly_AccXRefPointQly(expected) _stubs_check_E_accXRefPointQly_AccXRefPointQly(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_accXRefPointQly_AccXRefPointQly(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_accYRefPointQly_AccYRefPointQly(expected) _stubs_check_E_accYRefPointQly_AccYRefPointQly(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_accYRefPointQly_AccYRefPointQly(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_yawRateRearAxleQly_YawRateRearAxleQly(expected) _stubs_check_E_yawRateRearAxleQly_YawRateRearAxleQly(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_yawRateRearAxleQly_YawRateRearAxleQly(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_yawAccRearAxleQly_YawAccRearAxleQly(expected) _stubs_check_E_yawAccRearAxleQly_YawAccRearAxleQly(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_yawAccRearAxleQly_YawAccRearAxleQly(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_sideslipRefPointQly_SideslipRefPointQly(expected) _stubs_check_E_sideslipRefPointQly_SideslipRefPointQly(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_sideslipRefPointQly_SideslipRefPointQly(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_roadWheelAngleQly_RoadWheelAngleQly(expected) _stubs_check_E_roadWheelAngleQly_RoadWheelAngleQly(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_roadWheelAngleQly_RoadWheelAngleQly(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_crvtPathRefPointQly_CrvtPathRefPointQly(expected) _stubs_check_E_crvtPathRefPointQly_CrvtPathRefPointQly(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_crvtPathRefPointQly_CrvtPathRefPointQly(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_equivalentRearAxlePositionQly_EquivalentRearAxlePositionQly(expected) _stubs_check_E_equivalentRearAxlePositionQly_EquivalentRearAxlePositionQly(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_equivalentRearAxlePositionQly_EquivalentRearAxlePositionQly(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_V_spdYRefPoint_SpdYRefPoint(expected) _stubs_check_V_spdYRefPoint_SpdYRefPoint(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_V_spdYRefPoint_SpdYRefPoint(Speed_T* expected, const char *file, const char *function, const int line);

#define stubs_check_V_spdAtWhl_Ax1L_V_spdAtWhl_Ax1L(expected) _stubs_check_V_spdAtWhl_Ax1L_V_spdAtWhl_Ax1L(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_V_spdAtWhl_Ax1L_V_spdAtWhl_Ax1L(V_spdAtWhl_Ax1L_T* expected, const char *file, const char *function, const int line);

#define stubs_check_V_spdAtWhl_Ax1R_V_spdAtWhl_Ax1R(expected) _stubs_check_V_spdAtWhl_Ax1R_V_spdAtWhl_Ax1R(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_V_spdAtWhl_Ax1R_V_spdAtWhl_Ax1R(V_spdAtWhl_Ax1R_T* expected, const char *file, const char *function, const int line);

#define stubs_check_V_spdAtWhl_Ax2L_V_spdAtWhl_Ax2L(expected) _stubs_check_V_spdAtWhl_Ax2L_V_spdAtWhl_Ax2L(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_V_spdAtWhl_Ax2L_V_spdAtWhl_Ax2L(V_spdAtWhl_Ax2L_T* expected, const char *file, const char *function, const int line);

#define stubs_check_V_spdAtWhl_Ax2R_V_spdAtWhl_Ax2R(expected) _stubs_check_V_spdAtWhl_Ax2R_V_spdAtWhl_Ax2R(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_V_spdAtWhl_Ax2R_V_spdAtWhl_Ax2R(V_spdAtWhl_Ax2R_T* expected, const char *file, const char *function, const int line);

#define stubs_check_V_spdAtWhl_Ax3L_V_spdAtWhl_Ax3L(expected) _stubs_check_V_spdAtWhl_Ax3L_V_spdAtWhl_Ax3L(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_V_spdAtWhl_Ax3L_V_spdAtWhl_Ax3L(V_spdAtWhl_Ax3L_T* expected, const char *file, const char *function, const int line);

#define stubs_check_V_spdAtWhl_Ax3R_V_spdAtWhl_Ax3R(expected) _stubs_check_V_spdAtWhl_Ax3R_V_spdAtWhl_Ax3R(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_V_spdAtWhl_Ax3R_V_spdAtWhl_Ax3R(V_spdAtWhl_Ax3R_T* expected, const char *file, const char *function, const int line);

#define stubs_check_V_spdAtWhl_Ax4L_V_spdAtWhl_Ax4L(expected) _stubs_check_V_spdAtWhl_Ax4L_V_spdAtWhl_Ax4L(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_V_spdAtWhl_Ax4L_V_spdAtWhl_Ax4L(V_spdAtWhl_Ax4L_T* expected, const char *file, const char *function, const int line);

#define stubs_check_V_spdAtWhl_Ax4R_V_spdAtWhl_Ax4R(expected) _stubs_check_V_spdAtWhl_Ax4R_V_spdAtWhl_Ax4R(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_V_spdAtWhl_Ax4R_V_spdAtWhl_Ax4R(V_spdAtWhl_Ax4R_T* expected, const char *file, const char *function, const int line);

#define stubs_check_V_spdAtWhl_Ax5L_V_spdAtWhl_Ax5L(expected) _stubs_check_V_spdAtWhl_Ax5L_V_spdAtWhl_Ax5L(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_V_spdAtWhl_Ax5L_V_spdAtWhl_Ax5L(V_spdAtWhl_Ax5L_T* expected, const char *file, const char *function, const int line);

#define stubs_check_V_spdAtWhl_Ax5R_V_spdAtWhl_Ax5R(expected) _stubs_check_V_spdAtWhl_Ax5R_V_spdAtWhl_Ax5R(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_V_spdAtWhl_Ax5R_V_spdAtWhl_Ax5R(V_spdAtWhl_Ax5R_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_spdAtWhlQly_Ax1L_E_spdAtWhlQly_Ax1L(expected) _stubs_check_E_spdAtWhlQly_Ax1L_E_spdAtWhlQly_Ax1L(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_spdAtWhlQly_Ax1L_E_spdAtWhlQly_Ax1L(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_spdAtWhlQly_Ax1R_E_spdAtWhlQly_Ax1R(expected) _stubs_check_E_spdAtWhlQly_Ax1R_E_spdAtWhlQly_Ax1R(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_spdAtWhlQly_Ax1R_E_spdAtWhlQly_Ax1R(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_spdAtWhlQly_Ax2L_E_spdAtWhlQly_Ax2L(expected) _stubs_check_E_spdAtWhlQly_Ax2L_E_spdAtWhlQly_Ax2L(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_spdAtWhlQly_Ax2L_E_spdAtWhlQly_Ax2L(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_spdAtWhlQly_Ax2R_E_spdAtWhlQly_Ax2R(expected) _stubs_check_E_spdAtWhlQly_Ax2R_E_spdAtWhlQly_Ax2R(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_spdAtWhlQly_Ax2R_E_spdAtWhlQly_Ax2R(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_spdAtWhlQly_Ax3L_E_spdAtWhlQly_Ax3L(expected) _stubs_check_E_spdAtWhlQly_Ax3L_E_spdAtWhlQly_Ax3L(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_spdAtWhlQly_Ax3L_E_spdAtWhlQly_Ax3L(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_spdAtWhlQly_Ax3R_E_spdAtWhlQly_Ax3R(expected) _stubs_check_E_spdAtWhlQly_Ax3R_E_spdAtWhlQly_Ax3R(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_spdAtWhlQly_Ax3R_E_spdAtWhlQly_Ax3R(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_spdAtWhlQly_Ax4L_E_spdAtWhlQly_Ax4L(expected) _stubs_check_E_spdAtWhlQly_Ax4L_E_spdAtWhlQly_Ax4L(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_spdAtWhlQly_Ax4L_E_spdAtWhlQly_Ax4L(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_spdAtWhlQly_Ax4R_E_spdAtWhlQly_Ax4R(expected) _stubs_check_E_spdAtWhlQly_Ax4R_E_spdAtWhlQly_Ax4R(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_spdAtWhlQly_Ax4R_E_spdAtWhlQly_Ax4R(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_spdAtWhlQly_Ax5R_E_spdAtWhlQly_Ax5R(expected) _stubs_check_E_spdAtWhlQly_Ax5R_E_spdAtWhlQly_Ax5R(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_spdAtWhlQly_Ax5R_E_spdAtWhlQly_Ax5R(SignalQuality_T* expected, const char *file, const char *function, const int line);

#define stubs_check_E_spdAtWhlQly_Ax5L_E_spdAtWhlQly_Ax5L(expected) _stubs_check_E_spdAtWhlQly_Ax5L_E_spdAtWhlQly_Ax5L(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_E_spdAtWhlQly_Ax5L_E_spdAtWhlQly_Ax5L(SignalQuality_T* expected, const char *file, const char *function, const int line);

#endif
