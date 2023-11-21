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
