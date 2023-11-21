#define DISABLE_RTE_PTR2ARRAYBASETYPE_PASSING

#include "cunit_stubs.h"

StubSignals_Type p;

Std_ReturnType Rte_Read_ASREngineControlActive_ASREngineControlActive(PassiveActive2_T* par)
{
	*par = p.Rte_ASREngineControlActive_ASREngineControlActive.par;
	return p.Rte_ASREngineControlActive_ASREngineControlActive.ret;
}

Std_ReturnType Rte_Read_ActualEnginePercentTorque_ActualEnginePercentTorque(Percent8bit125NegOffset_T* par)
{
	*par = p.Rte_ActualEnginePercentTorque_ActualEnginePercentTorque.par;
	return p.Rte_ActualEnginePercentTorque_ActualEnginePercentTorque.ret;
}

Std_ReturnType Rte_Read_ActualDrvlnRetdrPercentTorque_ActualDrvlnRetdrPercentTorque(Percent8bit125NegOffset_T* par)
{
	*par = p.Rte_ActualDrvlnRetdrPercentTorque_ActualDrvlnRetdrPercentTorque.par;
	return p.Rte_ActualDrvlnRetdrPercentTorque_ActualDrvlnRetdrPercentTorque.ret;
}

Std_ReturnType Rte_Read_EngineReferenceTorque_EngineReferenceTorque(Torque16bit_T* par)
{
	*par = p.Rte_EngineReferenceTorque_EngineReferenceTorque.par;
	return p.Rte_EngineReferenceTorque_EngineReferenceTorque.ret;
}

Std_ReturnType Rte_Read_TransmissionActualGearRatio_TransmissionActualGearRatio(TransmissionActualGearRatio_T* par)
{
	*par = p.Rte_TransmissionActualGearRatio_TransmissionActualGearRatio.par;
	return p.Rte_TransmissionActualGearRatio_TransmissionActualGearRatio.ret;
}

Std_ReturnType Rte_Read_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged(DisengageEngage_T* par)
{
	*par = p.Rte_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged.par;
	return p.Rte_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged.ret;
}

Std_ReturnType Rte_Read_RoadInclinationPerc_RoadInclinationPerc(RoadInclinationPerc_T* par)
{
	*par = p.Rte_RoadInclinationPerc_RoadInclinationPerc.par;
	return p.Rte_RoadInclinationPerc_RoadInclinationPerc.ret;
}

Std_ReturnType Rte_Read_ASRBrakeControlActive_ASRBrakeControlActive(PassiveActive2_T* par)
{
	*par = p.Rte_ASRBrakeControlActive_ASRBrakeControlActive.par;
	return p.Rte_ASRBrakeControlActive_ASRBrakeControlActive.ret;
}

Std_ReturnType Rte_Read_ActualEHPusherWheelAngle_ActuaEHPusherWheelAngle(uint16* par)
{
	*par = p.Rte_ActualEHPusherWheelAngle_ActuaEHPusherWheelAngle.par;
	return p.Rte_ActualEHPusherWheelAngle_ActuaEHPusherWheelAngle.ret;
}

Std_ReturnType Rte_Read_ActualEHTagWheelAngle_ActualEHTagWheelAngle(uint16* par)
{
	*par = p.Rte_ActualEHTagWheelAngle_ActualEHTagWheelAngle.par;
	return p.Rte_ActualEHTagWheelAngle_ActualEHTagWheelAngle.ret;
}

Std_ReturnType Rte_Read_ActualTagWheelAngle_ActualTagWheelAngle(ActualTagWheelAngle_T* par)
{
	*par = p.Rte_ActualTagWheelAngle_ActualTagWheelAngle.par;
	return p.Rte_ActualTagWheelAngle_ActualTagWheelAngle.ret;
}

Std_ReturnType Rte_Read_DriveAxleLoad_AxleLoad(AxleLoad_T* par)
{
	*par = p.Rte_DriveAxleLoad_AxleLoad.par;
	return p.Rte_DriveAxleLoad_AxleLoad.ret;
}

Std_ReturnType Rte_Read_FrAxleLtWhlBrakeApplPrsHiRng_FrAxleLtWhlBrakeApplPrsHiRng(PressureFactor5_T* par)
{
	*par = p.Rte_FrAxleLtWhlBrakeApplPrsHiRng_FrAxleLtWhlBrakeApplPrsHiRng.par;
	return p.Rte_FrAxleLtWhlBrakeApplPrsHiRng_FrAxleLtWhlBrakeApplPrsHiRng.ret;
}

Std_ReturnType Rte_Read_FrAxleRtWhlBrakeApplPrsHiRng_FrAxleRtWhlBrakeApplPrsHiRng(PressureFactor5_T* par)
{
	*par = p.Rte_FrAxleRtWhlBrakeApplPrsHiRng_FrAxleRtWhlBrakeApplPrsHiRng.par;
	return p.Rte_FrAxleRtWhlBrakeApplPrsHiRng_FrAxleRtWhlBrakeApplPrsHiRng.ret;
}

Std_ReturnType Rte_Read_FrontAxle1Load_AxleLoad(AxleLoad_T* par)
{
	*par = p.Rte_FrontAxle1Load_AxleLoad.par;
	return p.Rte_FrontAxle1Load_AxleLoad.ret;
}

Std_ReturnType Rte_Read_FrontAxle2Load_AxleLoad(AxleLoad_T* par)
{
	*par = p.Rte_FrontAxle2Load_AxleLoad.par;
	return p.Rte_FrontAxle2Load_AxleLoad.ret;
}

Std_ReturnType Rte_Read_FrontAxleLeftWheelSpeed_FrontAxleLeftWheelSpeed(Speed16bit_T* par)
{
	*par = p.Rte_FrontAxleLeftWheelSpeed_FrontAxleLeftWheelSpeed.par;
	return p.Rte_FrontAxleLeftWheelSpeed_FrontAxleLeftWheelSpeed.ret;
}

Std_ReturnType Rte_Read_FrontAxleRightWheelSpeed_FrontAxleRightWheelSpeed(Speed16bit_T* par)
{
	*par = p.Rte_FrontAxleRightWheelSpeed_FrontAxleRightWheelSpeed.par;
	return p.Rte_FrontAxleRightWheelSpeed_FrontAxleRightWheelSpeed.ret;
}

Std_ReturnType Rte_Read_FrontRoadWheelAngleEstimate_FrontRoadWheelAngleEstimate(RWhlAg_T* par)
{
	*par = p.Rte_FrontRoadWheelAngleEstimate_FrontRoadWheelAngleEstimate.par;
	return p.Rte_FrontRoadWheelAngleEstimate_FrontRoadWheelAngleEstimate.ret;
}

Std_ReturnType Rte_Read_KFactor_KFactor(KFactor_T* par)
{
	*par = p.Rte_KFactor_KFactor.par;
	return p.Rte_KFactor_KFactor.ret;
}

Std_ReturnType Rte_Read_LiftAxle1PositionStatus_LiftAxle1PositionStatus(LiftAxlePositionStatus_T* par)
{
	*par = p.Rte_LiftAxle1PositionStatus_LiftAxle1PositionStatus.par;
	return p.Rte_LiftAxle1PositionStatus_LiftAxle1PositionStatus.ret;
}

Std_ReturnType Rte_Read_LiftAxle2PositionStatus_LiftAxle2PositionStatus(LiftAxlePositionStatus_T* par)
{
	*par = p.Rte_LiftAxle2PositionStatus_LiftAxle2PositionStatus.par;
	return p.Rte_LiftAxle2PositionStatus_LiftAxle2PositionStatus.ret;
}

Std_ReturnType Rte_Read_LongitudinalAcceleration_LongitudinalAcceleration(Acceleration16bit_T* par)
{
	*par = p.Rte_LongitudinalAcceleration_LongitudinalAcceleration.par;
	return p.Rte_LongitudinalAcceleration_LongitudinalAcceleration.ret;
}

Std_ReturnType Rte_Read_PusherAxleLoad_AxleLoad(AxleLoad_T* par)
{
	*par = p.Rte_PusherAxleLoad_AxleLoad.par;
	return p.Rte_PusherAxleLoad_AxleLoad.ret;
}

Std_ReturnType Rte_Read_RearAxleLeftWheelSpeed_RearAxleLeftWheelSpeed(Speed16bit_T* par)
{
	*par = p.Rte_RearAxleLeftWheelSpeed_RearAxleLeftWheelSpeed.par;
	return p.Rte_RearAxleLeftWheelSpeed_RearAxleLeftWheelSpeed.ret;
}

Std_ReturnType Rte_Read_RearAxleRightWheelSpeed_RearAxleRightWheelSpeed(Speed16bit_T* par)
{
	*par = p.Rte_RearAxleRightWheelSpeed_RearAxleRightWheelSpeed.par;
	return p.Rte_RearAxleRightWheelSpeed_RearAxleRightWheelSpeed.ret;
}

Std_ReturnType Rte_Read_RearAxleSteeringFunctionStatus_RearAxleSteeringFunctionStatus(RearAxleSteeringFunctionStatus_T* par)
{
	*par = p.Rte_RearAxleSteeringFunctionStatus_RearAxleSteeringFunctionStatus.par;
	return p.Rte_RearAxleSteeringFunctionStatus_RearAxleSteeringFunctionStatus.ret;
}

Std_ReturnType Rte_Read_RrAxle1LtWhlBrakeApplPrsHiRng_RrAxle1LtWhlBrakeApplPrsHiRng(PressureFactor5_T* par)
{
	*par = p.Rte_RrAxle1LtWhlBrakeApplPrsHiRng_RrAxle1LtWhlBrakeApplPrsHiRng.par;
	return p.Rte_RrAxle1LtWhlBrakeApplPrsHiRng_RrAxle1LtWhlBrakeApplPrsHiRng.ret;
}

Std_ReturnType Rte_Read_RrAxle1RtWhlBrakeApplPrsHiRng_RrAxle1RtWhlBrakeApplPrsHiRng(PressureFactor5_T* par)
{
	*par = p.Rte_RrAxle1RtWhlBrakeApplPrsHiRng_RrAxle1RtWhlBrakeApplPrsHiRng.par;
	return p.Rte_RrAxle1RtWhlBrakeApplPrsHiRng_RrAxle1RtWhlBrakeApplPrsHiRng.ret;
}

Std_ReturnType Rte_Read_RrAxle2LtWhlBrakeApplPrsHiRng_RrAxle2LtWhlBrakeApplPrsHiRng(PressureFactor5_T* par)
{
	*par = p.Rte_RrAxle2LtWhlBrakeApplPrsHiRng_RrAxle2LtWhlBrakeApplPrsHiRng.par;
	return p.Rte_RrAxle2LtWhlBrakeApplPrsHiRng_RrAxle2LtWhlBrakeApplPrsHiRng.ret;
}

Std_ReturnType Rte_Read_RrAxle2RtWhlBrakeApplPrsHiRng_RrAxle2RtWhlBrakeApplPrsHiRng(PressureFactor5_T* par)
{
	*par = p.Rte_RrAxle2RtWhlBrakeApplPrsHiRng_RrAxle2RtWhlBrakeApplPrsHiRng.par;
	return p.Rte_RrAxle2RtWhlBrakeApplPrsHiRng_RrAxle2RtWhlBrakeApplPrsHiRng.ret;
}

Std_ReturnType Rte_Read_RrAxle3LtWhlBrakeApplPrsHiRng_RrAxle3LtWhlBrakeApplPrsHiRng(PressureFactor5_T* par)
{
	*par = p.Rte_RrAxle3LtWhlBrakeApplPrsHiRng_RrAxle3LtWhlBrakeApplPrsHiRng.par;
	return p.Rte_RrAxle3LtWhlBrakeApplPrsHiRng_RrAxle3LtWhlBrakeApplPrsHiRng.ret;
}

Std_ReturnType Rte_Read_RrAxle3RtWhlBrakeApplPrsHiRng_RrAxle3RtWhlBrakeApplPrsHiRng(PressureFactor5_T* par)
{
	*par = p.Rte_RrAxle3RtWhlBrakeApplPrsHiRng_RrAxle3RtWhlBrakeApplPrsHiRng.par;
	return p.Rte_RrAxle3RtWhlBrakeApplPrsHiRng_RrAxle3RtWhlBrakeApplPrsHiRng.ret;
}

Std_ReturnType Rte_Read_SecondaryDriveAxleLoad_AxleLoad(AxleLoad_T* par)
{
	*par = p.Rte_SecondaryDriveAxleLoad_AxleLoad.par;
	return p.Rte_SecondaryDriveAxleLoad_AxleLoad.ret;
}

Std_ReturnType Rte_Read_SteeringWheelAngle_SteeringWheelAngle(SteeringWheelAngle_T* par)
{
	*par = p.Rte_SteeringWheelAngle_SteeringWheelAngle.par;
	return p.Rte_SteeringWheelAngle_SteeringWheelAngle.ret;
}

Std_ReturnType Rte_Read_TagAxleLoad_AxleLoad(AxleLoad_T* par)
{
	*par = p.Rte_TagAxleLoad_AxleLoad.par;
	return p.Rte_TagAxleLoad_AxleLoad.ret;
}

Std_ReturnType Rte_Read_TransmOutputShaftSpeedSigned_TransmOutputShaftSpeedSigned(SpeedRpm16bitMinus4000_T* par)
{
	*par = p.Rte_TransmOutputShaftSpeedSigned_TransmOutputShaftSpeedSigned.par;
	return p.Rte_TransmOutputShaftSpeedSigned_TransmOutputShaftSpeedSigned.ret;
}

Std_ReturnType Rte_Read_XPRsystemstate_XPRsystemstate(XPRsystemstate_T* par)
{
	*par = p.Rte_XPRsystemstate_XPRsystemstate.par;
	return p.Rte_XPRsystemstate_XPRsystemstate.ret;
}

Std_ReturnType Rte_Read_YawRate_YawRate(uint16* par)
{
	*par = p.Rte_YawRate_YawRate.par;
	return p.Rte_YawRate_YawRate.ret;
}

Std_ReturnType Rte_Read_VehicleMode_VehicleMode(VehicleMode_T* par)
{
	*par = p.Rte_VehicleMode_VehicleMode.par;
	return p.Rte_VehicleMode_VehicleMode.ret;
}

Std_ReturnType Rte_Read_ActualEngineRetarderPercentTrq_ActualEngineRetarderPercentTrq(Percent8bit125NegOffset_T* par)
{
	*par = p.Rte_ActualEngineRetarderPercentTrq_ActualEngineRetarderPercentTrq.par;
	return p.Rte_ActualEngineRetarderPercentTrq_ActualEngineRetarderPercentTrq.ret;
}

Std_ReturnType Rte_Write_AgrV_yawChassis_YawRateChassis(YawRateChassis_T const* par)
{
	p.Rte_AgrV_yawChassis_YawRateChassis.par = *par;
	return p.Rte_AgrV_yawChassis_YawRateChassis.ret;
}

Std_ReturnType Rte_Write_AgrA_yawChassis_YawAccChassis(YawAccChassis_T const* par)
{
	p.Rte_AgrA_yawChassis_YawAccChassis.par = *par;
	return p.Rte_AgrA_yawChassis_YawAccChassis.ret;
}

Std_ReturnType Rte_Write_V_spdXRefPoint_SpdXRefPoint(Speed_T const* par)
{
	p.Rte_V_spdXRefPoint_SpdXRefPoint.par = *par;
	return p.Rte_V_spdXRefPoint_SpdXRefPoint.ret;
}

Std_ReturnType Rte_Write_A_accXRefPoint_AccXRefPoint(Acceleration_T const* par)
{
	p.Rte_A_accXRefPoint_AccXRefPoint.par = *par;
	return p.Rte_A_accXRefPoint_AccXRefPoint.ret;
}

Std_ReturnType Rte_Write_A_accYRefPoint_AccYRefPoint(Acceleration_T const* par)
{
	p.Rte_A_accYRefPoint_AccYRefPoint.par = *par;
	return p.Rte_A_accYRefPoint_AccYRefPoint.ret;
}

Std_ReturnType Rte_Write_Ag_sideslipRefPoint_SideslipRefPoint(Angle_T const* par)
{
	p.Rte_Ag_sideslipRefPoint_SideslipRefPoint.par = *par;
	return p.Rte_Ag_sideslipRefPoint_SideslipRefPoint.ret;
}

Std_ReturnType Rte_Write_Crvt_pathRefPoint_CrvtPathRefPoint(Curvature_T const* par)
{
	p.Rte_Crvt_pathRefPoint_CrvtPathRefPoint.par = *par;
	return p.Rte_Crvt_pathRefPoint_CrvtPathRefPoint.ret;
}

Std_ReturnType Rte_Write_N_crvtFacRefPoint_CrvtFacRefPoint(CurvatureFac_T const* par)
{
	p.Rte_N_crvtFacRefPoint_CrvtFacRefPoint.par = *par;
	return p.Rte_N_crvtFacRefPoint_CrvtFacRefPoint.ret;
}

Std_ReturnType Rte_Write_L_equivalentRearAxlePosition_EquivalentRearAxlePos(EquivalentRearAxlePos_T const* par)
{
	p.Rte_L_equivalentRearAxlePosition_EquivalentRearAxlePos.par = *par;
	return p.Rte_L_equivalentRearAxlePosition_EquivalentRearAxlePos.ret;
}

Std_ReturnType Rte_Write_E_motionEstStatus_MotionEstStatus(MotionEstStatus_T const* par)
{
	p.Rte_E_motionEstStatus_MotionEstStatus.par = *par;
	return p.Rte_E_motionEstStatus_MotionEstStatus.ret;
}

Std_ReturnType Rte_Write_D_yawRateVari_YawRateVari(Variance_T const* par)
{
	p.Rte_D_yawRateVari_YawRateVari.par = *par;
	return p.Rte_D_yawRateVari_YawRateVari.ret;
}

Std_ReturnType Rte_Write_D_yawAccVari_YawAccVari(Variance_T const* par)
{
	p.Rte_D_yawAccVari_YawAccVari.par = *par;
	return p.Rte_D_yawAccVari_YawAccVari.ret;
}

Std_ReturnType Rte_Write_D_spdXVari_SpdXVari(Variance_T const* par)
{
	p.Rte_D_spdXVari_SpdXVari.par = *par;
	return p.Rte_D_spdXVari_SpdXVari.ret;
}

Std_ReturnType Rte_Write_D_spdYVari_SpdYVari(Variance_T const* par)
{
	p.Rte_D_spdYVari_SpdYVari.par = *par;
	return p.Rte_D_spdYVari_SpdYVari.ret;
}

Std_ReturnType Rte_Write_D_accXVari_AccXVari(Variance_T const* par)
{
	p.Rte_D_accXVari_AccXVari.par = *par;
	return p.Rte_D_accXVari_AccXVari.ret;
}

Std_ReturnType Rte_Write_D_accYVari_AccYVari(Variance_T const* par)
{
	p.Rte_D_accYVari_AccYVari.par = *par;
	return p.Rte_D_accYVari_AccYVari.ret;
}

Std_ReturnType Rte_Write_D_sideslipVari_SideslipVari(Variance_T const* par)
{
	p.Rte_D_sideslipVari_SideslipVari.par = *par;
	return p.Rte_D_sideslipVari_SideslipVari.ret;
}

Std_ReturnType Rte_Write_T_totalFilterLatencyEst_TotalFilterLatencyEst(Latency_T const* par)
{
	p.Rte_T_totalFilterLatencyEst_TotalFilterLatencyEst.par = *par;
	return p.Rte_T_totalFilterLatencyEst_TotalFilterLatencyEst.ret;
}

Std_ReturnType Rte_Write_Ag_chassisRollAngleEst_RollAngleChassisEst(Angle_T const* par)
{
	p.Rte_Ag_chassisRollAngleEst_RollAngleChassisEst.par = *par;
	return p.Rte_Ag_chassisRollAngleEst_RollAngleChassisEst.ret;
}

Std_ReturnType Rte_Write_E_chassisRollAngleEstQuality_RollAngleChassisEstQuality(RollAngleEstQly_T const* par)
{
	p.Rte_E_chassisRollAngleEstQuality_RollAngleChassisEstQuality.par = *par;
	return p.Rte_E_chassisRollAngleEstQuality_RollAngleChassisEstQuality.ret;
}

Std_ReturnType Rte_Write_A_spdXRateRefPoint_SpdXRateRefPoint(Acceleration_T const* par)
{
	p.Rte_A_spdXRateRefPoint_SpdXRateRefPoint.par = *par;
	return p.Rte_A_spdXRateRefPoint_SpdXRateRefPoint.ret;
}

Std_ReturnType Rte_Write_A_spdYRateRefPoint_SpdYRateRefPoint(Acceleration_T const* par)
{
	p.Rte_A_spdYRateRefPoint_SpdYRateRefPoint.par = *par;
	return p.Rte_A_spdYRateRefPoint_SpdYRateRefPoint.ret;
}

Std_ReturnType Rte_Write_Ag_roadWheelAngle_RoadWheelAngle(RoadWheelAngle_T2 const* par)
{
	p.Rte_Ag_roadWheelAngle_RoadWheelAngle.par = *par;
	return p.Rte_Ag_roadWheelAngle_RoadWheelAngle.ret;
}

Std_ReturnType Rte_Write_A_accYDueToBankAngle_AccYDueToBankAngle(Acceleration_T const* par)
{
	p.Rte_A_accYDueToBankAngle_AccYDueToBankAngle.par = *par;
	return p.Rte_A_accYDueToBankAngle_AccYDueToBankAngle.ret;
}

Std_ReturnType Rte_Write_LongMotionDirection_LongMotionDirection(LongMotionDirection_sg_T const* par)
{
	p.Rte_LongMotionDirection_LongMotionDirection.par = *par;
	return p.Rte_LongMotionDirection_LongMotionDirection.ret;
}

Std_ReturnType Rte_Write_LongMotionDirectionQuality_LongMotionDirectionQuality(LongMotionDirectionQuality_T const* par)
{
	p.Rte_LongMotionDirectionQuality_LongMotionDirectionQuality.par = *par;
	return p.Rte_LongMotionDirectionQuality_LongMotionDirectionQuality.ret;
}

Std_ReturnType Rte_Write_LongMotionDirection_ErrorStatus_LongMotionDirection_ErrorStatus(LongMotionDirErrorSts_T const* par)
{
	p.Rte_LongMotionDirection_ErrorStatus_LongMotionDirection_ErrorStatus.par = *par;
	return p.Rte_LongMotionDirection_ErrorStatus_LongMotionDirection_ErrorStatus.ret;
}

Std_ReturnType Rte_Write_D_nonlinearSteeringRatio_NonlinearSteeringRatio(SteeringRatio_T const* par)
{
	p.Rte_D_nonlinearSteeringRatio_NonlinearSteeringRatio.par = *par;
	return p.Rte_D_nonlinearSteeringRatio_NonlinearSteeringRatio.ret;
}

Std_ReturnType Rte_Write_E_spdXRefPointQly_SpdXRefPointQly(SignalQuality_T const* par)
{
	p.Rte_E_spdXRefPointQly_SpdXRefPointQly.par = *par;
	return p.Rte_E_spdXRefPointQly_SpdXRefPointQly.ret;
}

Std_ReturnType Rte_Write_E_spdYRefPointQly_SpdYRefPointQly(SignalQuality_T const* par)
{
	p.Rte_E_spdYRefPointQly_SpdYRefPointQly.par = *par;
	return p.Rte_E_spdYRefPointQly_SpdYRefPointQly.ret;
}

Std_ReturnType Rte_Write_E_accXRefPointQly_AccXRefPointQly(SignalQuality_T const* par)
{
	p.Rte_E_accXRefPointQly_AccXRefPointQly.par = *par;
	return p.Rte_E_accXRefPointQly_AccXRefPointQly.ret;
}

Std_ReturnType Rte_Write_E_accYRefPointQly_AccYRefPointQly(SignalQuality_T const* par)
{
	p.Rte_E_accYRefPointQly_AccYRefPointQly.par = *par;
	return p.Rte_E_accYRefPointQly_AccYRefPointQly.ret;
}

Std_ReturnType Rte_Write_E_yawRateRearAxleQly_YawRateRearAxleQly(SignalQuality_T const* par)
{
	p.Rte_E_yawRateRearAxleQly_YawRateRearAxleQly.par = *par;
	return p.Rte_E_yawRateRearAxleQly_YawRateRearAxleQly.ret;
}

Std_ReturnType Rte_Write_E_yawAccRearAxleQly_YawAccRearAxleQly(SignalQuality_T const* par)
{
	p.Rte_E_yawAccRearAxleQly_YawAccRearAxleQly.par = *par;
	return p.Rte_E_yawAccRearAxleQly_YawAccRearAxleQly.ret;
}

Std_ReturnType Rte_Write_E_sideslipRefPointQly_SideslipRefPointQly(SignalQuality_T const* par)
{
	p.Rte_E_sideslipRefPointQly_SideslipRefPointQly.par = *par;
	return p.Rte_E_sideslipRefPointQly_SideslipRefPointQly.ret;
}

Std_ReturnType Rte_Write_E_roadWheelAngleQly_RoadWheelAngleQly(SignalQuality_T const* par)
{
	p.Rte_E_roadWheelAngleQly_RoadWheelAngleQly.par = *par;
	return p.Rte_E_roadWheelAngleQly_RoadWheelAngleQly.ret;
}

Std_ReturnType Rte_Write_E_crvtPathRefPointQly_CrvtPathRefPointQly(SignalQuality_T const* par)
{
	p.Rte_E_crvtPathRefPointQly_CrvtPathRefPointQly.par = *par;
	return p.Rte_E_crvtPathRefPointQly_CrvtPathRefPointQly.ret;
}

Std_ReturnType Rte_Write_E_equivalentRearAxlePositionQly_EquivalentRearAxlePositionQly(SignalQuality_T const* par)
{
	p.Rte_E_equivalentRearAxlePositionQly_EquivalentRearAxlePositionQly.par = *par;
	return p.Rte_E_equivalentRearAxlePositionQly_EquivalentRearAxlePositionQly.ret;
}

Std_ReturnType Rte_Write_V_spdYRefPoint_SpdYRefPoint(Speed_T const* par)
{
	p.Rte_V_spdYRefPoint_SpdYRefPoint.par = *par;
	return p.Rte_V_spdYRefPoint_SpdYRefPoint.ret;
}

Std_ReturnType Rte_Write_V_spdAtWhl_Ax1L_V_spdAtWhl_Ax1L(V_spdAtWhl_Ax1L_T const* par)
{
	p.Rte_V_spdAtWhl_Ax1L_V_spdAtWhl_Ax1L.par = *par;
	return p.Rte_V_spdAtWhl_Ax1L_V_spdAtWhl_Ax1L.ret;
}

Std_ReturnType Rte_Write_V_spdAtWhl_Ax1R_V_spdAtWhl_Ax1R(V_spdAtWhl_Ax1R_T const* par)
{
	p.Rte_V_spdAtWhl_Ax1R_V_spdAtWhl_Ax1R.par = *par;
	return p.Rte_V_spdAtWhl_Ax1R_V_spdAtWhl_Ax1R.ret;
}

Std_ReturnType Rte_Write_V_spdAtWhl_Ax2L_V_spdAtWhl_Ax2L(V_spdAtWhl_Ax2L_T const* par)
{
	p.Rte_V_spdAtWhl_Ax2L_V_spdAtWhl_Ax2L.par = *par;
	return p.Rte_V_spdAtWhl_Ax2L_V_spdAtWhl_Ax2L.ret;
}

Std_ReturnType Rte_Write_V_spdAtWhl_Ax2R_V_spdAtWhl_Ax2R(V_spdAtWhl_Ax2R_T const* par)
{
	p.Rte_V_spdAtWhl_Ax2R_V_spdAtWhl_Ax2R.par = *par;
	return p.Rte_V_spdAtWhl_Ax2R_V_spdAtWhl_Ax2R.ret;
}

Std_ReturnType Rte_Write_V_spdAtWhl_Ax3L_V_spdAtWhl_Ax3L(V_spdAtWhl_Ax3L_T const* par)
{
	p.Rte_V_spdAtWhl_Ax3L_V_spdAtWhl_Ax3L.par = *par;
	return p.Rte_V_spdAtWhl_Ax3L_V_spdAtWhl_Ax3L.ret;
}

Std_ReturnType Rte_Write_V_spdAtWhl_Ax3R_V_spdAtWhl_Ax3R(V_spdAtWhl_Ax3R_T const* par)
{
	p.Rte_V_spdAtWhl_Ax3R_V_spdAtWhl_Ax3R.par = *par;
	return p.Rte_V_spdAtWhl_Ax3R_V_spdAtWhl_Ax3R.ret;
}

Std_ReturnType Rte_Write_V_spdAtWhl_Ax4L_V_spdAtWhl_Ax4L(V_spdAtWhl_Ax4L_T const* par)
{
	p.Rte_V_spdAtWhl_Ax4L_V_spdAtWhl_Ax4L.par = *par;
	return p.Rte_V_spdAtWhl_Ax4L_V_spdAtWhl_Ax4L.ret;
}

Std_ReturnType Rte_Write_V_spdAtWhl_Ax4R_V_spdAtWhl_Ax4R(V_spdAtWhl_Ax4R_T const* par)
{
	p.Rte_V_spdAtWhl_Ax4R_V_spdAtWhl_Ax4R.par = *par;
	return p.Rte_V_spdAtWhl_Ax4R_V_spdAtWhl_Ax4R.ret;
}

Std_ReturnType Rte_Write_V_spdAtWhl_Ax5L_V_spdAtWhl_Ax5L(V_spdAtWhl_Ax5L_T const* par)
{
	p.Rte_V_spdAtWhl_Ax5L_V_spdAtWhl_Ax5L.par = *par;
	return p.Rte_V_spdAtWhl_Ax5L_V_spdAtWhl_Ax5L.ret;
}

Std_ReturnType Rte_Write_V_spdAtWhl_Ax5R_V_spdAtWhl_Ax5R(V_spdAtWhl_Ax5R_T const* par)
{
	p.Rte_V_spdAtWhl_Ax5R_V_spdAtWhl_Ax5R.par = *par;
	return p.Rte_V_spdAtWhl_Ax5R_V_spdAtWhl_Ax5R.ret;
}

Std_ReturnType Rte_Write_E_spdAtWhlQly_Ax1L_E_spdAtWhlQly_Ax1L(SignalQuality_T const* par)
{
	p.Rte_E_spdAtWhlQly_Ax1L_E_spdAtWhlQly_Ax1L.par = *par;
	return p.Rte_E_spdAtWhlQly_Ax1L_E_spdAtWhlQly_Ax1L.ret;
}

Std_ReturnType Rte_Write_E_spdAtWhlQly_Ax1R_E_spdAtWhlQly_Ax1R(SignalQuality_T const* par)
{
	p.Rte_E_spdAtWhlQly_Ax1R_E_spdAtWhlQly_Ax1R.par = *par;
	return p.Rte_E_spdAtWhlQly_Ax1R_E_spdAtWhlQly_Ax1R.ret;
}

Std_ReturnType Rte_Write_E_spdAtWhlQly_Ax2L_E_spdAtWhlQly_Ax2L(SignalQuality_T const* par)
{
	p.Rte_E_spdAtWhlQly_Ax2L_E_spdAtWhlQly_Ax2L.par = *par;
	return p.Rte_E_spdAtWhlQly_Ax2L_E_spdAtWhlQly_Ax2L.ret;
}

Std_ReturnType Rte_Write_E_spdAtWhlQly_Ax2R_E_spdAtWhlQly_Ax2R(SignalQuality_T const* par)
{
	p.Rte_E_spdAtWhlQly_Ax2R_E_spdAtWhlQly_Ax2R.par = *par;
	return p.Rte_E_spdAtWhlQly_Ax2R_E_spdAtWhlQly_Ax2R.ret;
}

Std_ReturnType Rte_Write_E_spdAtWhlQly_Ax3L_E_spdAtWhlQly_Ax3L(SignalQuality_T const* par)
{
	p.Rte_E_spdAtWhlQly_Ax3L_E_spdAtWhlQly_Ax3L.par = *par;
	return p.Rte_E_spdAtWhlQly_Ax3L_E_spdAtWhlQly_Ax3L.ret;
}

Std_ReturnType Rte_Write_E_spdAtWhlQly_Ax3R_E_spdAtWhlQly_Ax3R(SignalQuality_T const* par)
{
	p.Rte_E_spdAtWhlQly_Ax3R_E_spdAtWhlQly_Ax3R.par = *par;
	return p.Rte_E_spdAtWhlQly_Ax3R_E_spdAtWhlQly_Ax3R.ret;
}

Std_ReturnType Rte_Write_E_spdAtWhlQly_Ax4L_E_spdAtWhlQly_Ax4L(SignalQuality_T const* par)
{
	p.Rte_E_spdAtWhlQly_Ax4L_E_spdAtWhlQly_Ax4L.par = *par;
	return p.Rte_E_spdAtWhlQly_Ax4L_E_spdAtWhlQly_Ax4L.ret;
}

Std_ReturnType Rte_Write_E_spdAtWhlQly_Ax4R_E_spdAtWhlQly_Ax4R(SignalQuality_T const* par)
{
	p.Rte_E_spdAtWhlQly_Ax4R_E_spdAtWhlQly_Ax4R.par = *par;
	return p.Rte_E_spdAtWhlQly_Ax4R_E_spdAtWhlQly_Ax4R.ret;
}

Std_ReturnType Rte_Write_E_spdAtWhlQly_Ax5R_E_spdAtWhlQly_Ax5R(SignalQuality_T const* par)
{
	p.Rte_E_spdAtWhlQly_Ax5R_E_spdAtWhlQly_Ax5R.par = *par;
	return p.Rte_E_spdAtWhlQly_Ax5R_E_spdAtWhlQly_Ax5R.ret;
}

Std_ReturnType Rte_Write_E_spdAtWhlQly_Ax5L_E_spdAtWhlQly_Ax5L(SignalQuality_T const* par)
{
	p.Rte_E_spdAtWhlQly_Ax5L_E_spdAtWhlQly_Ax5L.par = *par;
	return p.Rte_E_spdAtWhlQly_Ax5L_E_spdAtWhlQly_Ax5L.ret;
}

void stubs_set_ASREngineControlActive_ASREngineControlActive(PassiveActive2_T par)
{
	p.Rte_ASREngineControlActive_ASREngineControlActive.par = par;
}

void stubs_set_ActualEnginePercentTorque_ActualEnginePercentTorque(Percent8bit125NegOffset_T par)
{
	p.Rte_ActualEnginePercentTorque_ActualEnginePercentTorque.par = par;
}

void stubs_set_ActualDrvlnRetdrPercentTorque_ActualDrvlnRetdrPercentTorque(Percent8bit125NegOffset_T par)
{
	p.Rte_ActualDrvlnRetdrPercentTorque_ActualDrvlnRetdrPercentTorque.par = par;
}

void stubs_set_EngineReferenceTorque_EngineReferenceTorque(Torque16bit_T par)
{
	p.Rte_EngineReferenceTorque_EngineReferenceTorque.par = par;
}

void stubs_set_TransmissionActualGearRatio_TransmissionActualGearRatio(TransmissionActualGearRatio_T par)
{
	p.Rte_TransmissionActualGearRatio_TransmissionActualGearRatio.par = par;
}

void stubs_set_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged(DisengageEngage_T par)
{
	p.Rte_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged.par = par;
}

void stubs_set_RoadInclinationPerc_RoadInclinationPerc(RoadInclinationPerc_T par)
{
	p.Rte_RoadInclinationPerc_RoadInclinationPerc.par = par;
}

void stubs_set_ASRBrakeControlActive_ASRBrakeControlActive(PassiveActive2_T par)
{
	p.Rte_ASRBrakeControlActive_ASRBrakeControlActive.par = par;
}

void stubs_set_ActualEHPusherWheelAngle_ActuaEHPusherWheelAngle(uint16 par)
{
	p.Rte_ActualEHPusherWheelAngle_ActuaEHPusherWheelAngle.par = par;
}

void stubs_set_ActualEHTagWheelAngle_ActualEHTagWheelAngle(uint16 par)
{
	p.Rte_ActualEHTagWheelAngle_ActualEHTagWheelAngle.par = par;
}

void stubs_set_ActualTagWheelAngle_ActualTagWheelAngle(ActualTagWheelAngle_T par)
{
	p.Rte_ActualTagWheelAngle_ActualTagWheelAngle.par = par;
}

void stubs_set_DriveAxleLoad_AxleLoad(AxleLoad_T par)
{
	p.Rte_DriveAxleLoad_AxleLoad.par = par;
}

void stubs_set_FrAxleLtWhlBrakeApplPrsHiRng_FrAxleLtWhlBrakeApplPrsHiRng(PressureFactor5_T par)
{
	p.Rte_FrAxleLtWhlBrakeApplPrsHiRng_FrAxleLtWhlBrakeApplPrsHiRng.par = par;
}

void stubs_set_FrAxleRtWhlBrakeApplPrsHiRng_FrAxleRtWhlBrakeApplPrsHiRng(PressureFactor5_T par)
{
	p.Rte_FrAxleRtWhlBrakeApplPrsHiRng_FrAxleRtWhlBrakeApplPrsHiRng.par = par;
}

void stubs_set_FrontAxle1Load_AxleLoad(AxleLoad_T par)
{
	p.Rte_FrontAxle1Load_AxleLoad.par = par;
}

void stubs_set_FrontAxle2Load_AxleLoad(AxleLoad_T par)
{
	p.Rte_FrontAxle2Load_AxleLoad.par = par;
}

void stubs_set_FrontAxleLeftWheelSpeed_FrontAxleLeftWheelSpeed(Speed16bit_T par)
{
	p.Rte_FrontAxleLeftWheelSpeed_FrontAxleLeftWheelSpeed.par = par;
}

void stubs_set_FrontAxleRightWheelSpeed_FrontAxleRightWheelSpeed(Speed16bit_T par)
{
	p.Rte_FrontAxleRightWheelSpeed_FrontAxleRightWheelSpeed.par = par;
}

void stubs_set_FrontRoadWheelAngleEstimate_FrontRoadWheelAngleEstimate(RWhlAg_T par)
{
	p.Rte_FrontRoadWheelAngleEstimate_FrontRoadWheelAngleEstimate.par = par;
}

void stubs_set_KFactor_KFactor(KFactor_T par)
{
	p.Rte_KFactor_KFactor.par = par;
}

void stubs_set_LiftAxle1PositionStatus_LiftAxle1PositionStatus(LiftAxlePositionStatus_T par)
{
	p.Rte_LiftAxle1PositionStatus_LiftAxle1PositionStatus.par = par;
}

void stubs_set_LiftAxle2PositionStatus_LiftAxle2PositionStatus(LiftAxlePositionStatus_T par)
{
	p.Rte_LiftAxle2PositionStatus_LiftAxle2PositionStatus.par = par;
}

void stubs_set_LongitudinalAcceleration_LongitudinalAcceleration(Acceleration16bit_T par)
{
	p.Rte_LongitudinalAcceleration_LongitudinalAcceleration.par = par;
}

void stubs_set_PusherAxleLoad_AxleLoad(AxleLoad_T par)
{
	p.Rte_PusherAxleLoad_AxleLoad.par = par;
}

void stubs_set_RearAxleLeftWheelSpeed_RearAxleLeftWheelSpeed(Speed16bit_T par)
{
	p.Rte_RearAxleLeftWheelSpeed_RearAxleLeftWheelSpeed.par = par;
}

void stubs_set_RearAxleRightWheelSpeed_RearAxleRightWheelSpeed(Speed16bit_T par)
{
	p.Rte_RearAxleRightWheelSpeed_RearAxleRightWheelSpeed.par = par;
}

void stubs_set_RearAxleSteeringFunctionStatus_RearAxleSteeringFunctionStatus(RearAxleSteeringFunctionStatus_T par)
{
	p.Rte_RearAxleSteeringFunctionStatus_RearAxleSteeringFunctionStatus.par = par;
}

void stubs_set_RrAxle1LtWhlBrakeApplPrsHiRng_RrAxle1LtWhlBrakeApplPrsHiRng(PressureFactor5_T par)
{
	p.Rte_RrAxle1LtWhlBrakeApplPrsHiRng_RrAxle1LtWhlBrakeApplPrsHiRng.par = par;
}

void stubs_set_RrAxle1RtWhlBrakeApplPrsHiRng_RrAxle1RtWhlBrakeApplPrsHiRng(PressureFactor5_T par)
{
	p.Rte_RrAxle1RtWhlBrakeApplPrsHiRng_RrAxle1RtWhlBrakeApplPrsHiRng.par = par;
}

void stubs_set_RrAxle2LtWhlBrakeApplPrsHiRng_RrAxle2LtWhlBrakeApplPrsHiRng(PressureFactor5_T par)
{
	p.Rte_RrAxle2LtWhlBrakeApplPrsHiRng_RrAxle2LtWhlBrakeApplPrsHiRng.par = par;
}

void stubs_set_RrAxle2RtWhlBrakeApplPrsHiRng_RrAxle2RtWhlBrakeApplPrsHiRng(PressureFactor5_T par)
{
	p.Rte_RrAxle2RtWhlBrakeApplPrsHiRng_RrAxle2RtWhlBrakeApplPrsHiRng.par = par;
}

void stubs_set_RrAxle3LtWhlBrakeApplPrsHiRng_RrAxle3LtWhlBrakeApplPrsHiRng(PressureFactor5_T par)
{
	p.Rte_RrAxle3LtWhlBrakeApplPrsHiRng_RrAxle3LtWhlBrakeApplPrsHiRng.par = par;
}

void stubs_set_RrAxle3RtWhlBrakeApplPrsHiRng_RrAxle3RtWhlBrakeApplPrsHiRng(PressureFactor5_T par)
{
	p.Rte_RrAxle3RtWhlBrakeApplPrsHiRng_RrAxle3RtWhlBrakeApplPrsHiRng.par = par;
}

void stubs_set_SecondaryDriveAxleLoad_AxleLoad(AxleLoad_T par)
{
	p.Rte_SecondaryDriveAxleLoad_AxleLoad.par = par;
}

void stubs_set_SteeringWheelAngle_SteeringWheelAngle(SteeringWheelAngle_T par)
{
	p.Rte_SteeringWheelAngle_SteeringWheelAngle.par = par;
}

void stubs_set_TagAxleLoad_AxleLoad(AxleLoad_T par)
{
	p.Rte_TagAxleLoad_AxleLoad.par = par;
}

void stubs_set_TransmOutputShaftSpeedSigned_TransmOutputShaftSpeedSigned(SpeedRpm16bitMinus4000_T par)
{
	p.Rte_TransmOutputShaftSpeedSigned_TransmOutputShaftSpeedSigned.par = par;
}

void stubs_set_XPRsystemstate_XPRsystemstate(XPRsystemstate_T par)
{
	p.Rte_XPRsystemstate_XPRsystemstate.par = par;
}

void stubs_set_YawRate_YawRate(uint16 par)
{
	p.Rte_YawRate_YawRate.par = par;
}

void stubs_set_VehicleMode_VehicleMode(VehicleMode_T par)
{
	p.Rte_VehicleMode_VehicleMode.par = par;
}

void stubs_set_ActualEngineRetarderPercentTrq_ActualEngineRetarderPercentTrq(Percent8bit125NegOffset_T par)
{
	p.Rte_ActualEngineRetarderPercentTrq_ActualEngineRetarderPercentTrq.par = par;
}

void _stubs_check_AgrV_yawChassis_YawRateChassis(YawRateChassis_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_AgrV_yawChassis_YawRateChassis.par.YawRate != expected->YawRate)
	{
		printf("%s in %s on line: %d, YawRate: expected %d but was %d\n", file, function, line, expected->YawRate, p.Rte_AgrV_yawChassis_YawRateChassis.par.YawRate);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_AgrV_yawChassis_YawRateChassis.par.YawRate == expected->YawRate);
}

void _stubs_check_AgrA_yawChassis_YawAccChassis(YawAccChassis_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_AgrA_yawChassis_YawAccChassis.par.YawAcc != expected->YawAcc)
	{
		printf("%s in %s on line: %d, YawAcc: expected %d but was %d\n", file, function, line, expected->YawAcc, p.Rte_AgrA_yawChassis_YawAccChassis.par.YawAcc);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_AgrA_yawChassis_YawAccChassis.par.YawAcc == expected->YawAcc);
}

void _stubs_check_V_spdXRefPoint_SpdXRefPoint(Speed_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_V_spdXRefPoint_SpdXRefPoint.par.Speed != expected->Speed)
	{
		printf("%s in %s on line: %d, Speed: expected %d but was %d\n", file, function, line, expected->Speed, p.Rte_V_spdXRefPoint_SpdXRefPoint.par.Speed);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_V_spdXRefPoint_SpdXRefPoint.par.Speed == expected->Speed);
}

void _stubs_check_A_accXRefPoint_AccXRefPoint(Acceleration_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_A_accXRefPoint_AccXRefPoint.par.Acceleration != expected->Acceleration)
	{
		printf("%s in %s on line: %d, Acceleration: expected %d but was %d\n", file, function, line, expected->Acceleration, p.Rte_A_accXRefPoint_AccXRefPoint.par.Acceleration);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_A_accXRefPoint_AccXRefPoint.par.Acceleration == expected->Acceleration);
}

void _stubs_check_A_accYRefPoint_AccYRefPoint(Acceleration_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_A_accYRefPoint_AccYRefPoint.par.Acceleration != expected->Acceleration)
	{
		printf("%s in %s on line: %d, Acceleration: expected %d but was %d\n", file, function, line, expected->Acceleration, p.Rte_A_accYRefPoint_AccYRefPoint.par.Acceleration);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_A_accYRefPoint_AccYRefPoint.par.Acceleration == expected->Acceleration);
}

void _stubs_check_Ag_sideslipRefPoint_SideslipRefPoint(Angle_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_Ag_sideslipRefPoint_SideslipRefPoint.par.Angle != expected->Angle)
	{
		printf("%s in %s on line: %d, Angle: expected %d but was %d\n", file, function, line, expected->Angle, p.Rte_Ag_sideslipRefPoint_SideslipRefPoint.par.Angle);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_Ag_sideslipRefPoint_SideslipRefPoint.par.Angle == expected->Angle);
}

void _stubs_check_Crvt_pathRefPoint_CrvtPathRefPoint(Curvature_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_Crvt_pathRefPoint_CrvtPathRefPoint.par.Curvature != expected->Curvature)
	{
		printf("%s in %s on line: %d, Curvature: expected %d but was %d\n", file, function, line, expected->Curvature, p.Rte_Crvt_pathRefPoint_CrvtPathRefPoint.par.Curvature);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_Crvt_pathRefPoint_CrvtPathRefPoint.par.Curvature == expected->Curvature);
}

void _stubs_check_N_crvtFacRefPoint_CrvtFacRefPoint(CurvatureFac_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_N_crvtFacRefPoint_CrvtFacRefPoint.par.CurvatureFac != expected->CurvatureFac)
	{
		printf("%s in %s on line: %d, CurvatureFac: expected %d but was %d\n", file, function, line, expected->CurvatureFac, p.Rte_N_crvtFacRefPoint_CrvtFacRefPoint.par.CurvatureFac);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_N_crvtFacRefPoint_CrvtFacRefPoint.par.CurvatureFac == expected->CurvatureFac);
}

void _stubs_check_L_equivalentRearAxlePosition_EquivalentRearAxlePos(EquivalentRearAxlePos_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_L_equivalentRearAxlePosition_EquivalentRearAxlePos.par.EquivRrAxlePos != expected->EquivRrAxlePos)
	{
		printf("%s in %s on line: %d, EquivRrAxlePos: expected %d but was %d\n", file, function, line, expected->EquivRrAxlePos, p.Rte_L_equivalentRearAxlePosition_EquivalentRearAxlePos.par.EquivRrAxlePos);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_L_equivalentRearAxlePosition_EquivalentRearAxlePos.par.EquivRrAxlePos == expected->EquivRrAxlePos);
}

void _stubs_check_E_motionEstStatus_MotionEstStatus(MotionEstStatus_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_motionEstStatus_MotionEstStatus.par.MotionEstState != expected->MotionEstState)
	{
		printf("%s in %s on line: %d, MotionEstState: expected %d but was %d\n", file, function, line, expected->MotionEstState, p.Rte_E_motionEstStatus_MotionEstStatus.par.MotionEstState);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_motionEstStatus_MotionEstStatus.par.MotionEstState == expected->MotionEstState);
}

void _stubs_check_D_yawRateVari_YawRateVari(Variance_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_D_yawRateVari_YawRateVari.par.Variance != expected->Variance)
	{
		printf("%s in %s on line: %d, Variance: expected %d but was %d\n", file, function, line, expected->Variance, p.Rte_D_yawRateVari_YawRateVari.par.Variance);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_D_yawRateVari_YawRateVari.par.Variance == expected->Variance);
}

void _stubs_check_D_yawAccVari_YawAccVari(Variance_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_D_yawAccVari_YawAccVari.par.Variance != expected->Variance)
	{
		printf("%s in %s on line: %d, Variance: expected %d but was %d\n", file, function, line, expected->Variance, p.Rte_D_yawAccVari_YawAccVari.par.Variance);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_D_yawAccVari_YawAccVari.par.Variance == expected->Variance);
}

void _stubs_check_D_spdXVari_SpdXVari(Variance_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_D_spdXVari_SpdXVari.par.Variance != expected->Variance)
	{
		printf("%s in %s on line: %d, Variance: expected %d but was %d\n", file, function, line, expected->Variance, p.Rte_D_spdXVari_SpdXVari.par.Variance);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_D_spdXVari_SpdXVari.par.Variance == expected->Variance);
}

void _stubs_check_D_spdYVari_SpdYVari(Variance_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_D_spdYVari_SpdYVari.par.Variance != expected->Variance)
	{
		printf("%s in %s on line: %d, Variance: expected %d but was %d\n", file, function, line, expected->Variance, p.Rte_D_spdYVari_SpdYVari.par.Variance);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_D_spdYVari_SpdYVari.par.Variance == expected->Variance);
}

void _stubs_check_D_accXVari_AccXVari(Variance_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_D_accXVari_AccXVari.par.Variance != expected->Variance)
	{
		printf("%s in %s on line: %d, Variance: expected %d but was %d\n", file, function, line, expected->Variance, p.Rte_D_accXVari_AccXVari.par.Variance);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_D_accXVari_AccXVari.par.Variance == expected->Variance);
}

void _stubs_check_D_accYVari_AccYVari(Variance_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_D_accYVari_AccYVari.par.Variance != expected->Variance)
	{
		printf("%s in %s on line: %d, Variance: expected %d but was %d\n", file, function, line, expected->Variance, p.Rte_D_accYVari_AccYVari.par.Variance);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_D_accYVari_AccYVari.par.Variance == expected->Variance);
}

void _stubs_check_D_sideslipVari_SideslipVari(Variance_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_D_sideslipVari_SideslipVari.par.Variance != expected->Variance)
	{
		printf("%s in %s on line: %d, Variance: expected %d but was %d\n", file, function, line, expected->Variance, p.Rte_D_sideslipVari_SideslipVari.par.Variance);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_D_sideslipVari_SideslipVari.par.Variance == expected->Variance);
}

void _stubs_check_T_totalFilterLatencyEst_TotalFilterLatencyEst(Latency_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_T_totalFilterLatencyEst_TotalFilterLatencyEst.par.Latency != expected->Latency)
	{
		printf("%s in %s on line: %d, Latency: expected %d but was %d\n", file, function, line, expected->Latency, p.Rte_T_totalFilterLatencyEst_TotalFilterLatencyEst.par.Latency);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_T_totalFilterLatencyEst_TotalFilterLatencyEst.par.Latency == expected->Latency);
}

void _stubs_check_Ag_chassisRollAngleEst_RollAngleChassisEst(Angle_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_Ag_chassisRollAngleEst_RollAngleChassisEst.par.Angle != expected->Angle)
	{
		printf("%s in %s on line: %d, Angle: expected %d but was %d\n", file, function, line, expected->Angle, p.Rte_Ag_chassisRollAngleEst_RollAngleChassisEst.par.Angle);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_Ag_chassisRollAngleEst_RollAngleChassisEst.par.Angle == expected->Angle);
}

void _stubs_check_E_chassisRollAngleEstQuality_RollAngleChassisEstQuality(RollAngleEstQly_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_chassisRollAngleEstQuality_RollAngleChassisEstQuality.par.RollAngleEstQly != expected->RollAngleEstQly)
	{
		printf("%s in %s on line: %d, RollAngleEstQly: expected %d but was %d\n", file, function, line, expected->RollAngleEstQly, p.Rte_E_chassisRollAngleEstQuality_RollAngleChassisEstQuality.par.RollAngleEstQly);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_chassisRollAngleEstQuality_RollAngleChassisEstQuality.par.RollAngleEstQly == expected->RollAngleEstQly);
}

void _stubs_check_A_spdXRateRefPoint_SpdXRateRefPoint(Acceleration_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_A_spdXRateRefPoint_SpdXRateRefPoint.par.Acceleration != expected->Acceleration)
	{
		printf("%s in %s on line: %d, Acceleration: expected %d but was %d\n", file, function, line, expected->Acceleration, p.Rte_A_spdXRateRefPoint_SpdXRateRefPoint.par.Acceleration);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_A_spdXRateRefPoint_SpdXRateRefPoint.par.Acceleration == expected->Acceleration);
}

void _stubs_check_A_spdYRateRefPoint_SpdYRateRefPoint(Acceleration_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_A_spdYRateRefPoint_SpdYRateRefPoint.par.Acceleration != expected->Acceleration)
	{
		printf("%s in %s on line: %d, Acceleration: expected %d but was %d\n", file, function, line, expected->Acceleration, p.Rte_A_spdYRateRefPoint_SpdYRateRefPoint.par.Acceleration);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_A_spdYRateRefPoint_SpdYRateRefPoint.par.Acceleration == expected->Acceleration);
}

void _stubs_check_Ag_roadWheelAngle_RoadWheelAngle(RoadWheelAngle_T2* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_Ag_roadWheelAngle_RoadWheelAngle.par.RoadWheelAngle != expected->RoadWheelAngle)
	{
		printf("%s in %s on line: %d, RoadWheelAngle: expected %d but was %d\n", file, function, line, expected->RoadWheelAngle, p.Rte_Ag_roadWheelAngle_RoadWheelAngle.par.RoadWheelAngle);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_Ag_roadWheelAngle_RoadWheelAngle.par.RoadWheelAngle == expected->RoadWheelAngle);
}

void _stubs_check_A_accYDueToBankAngle_AccYDueToBankAngle(Acceleration_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_A_accYDueToBankAngle_AccYDueToBankAngle.par.Acceleration != expected->Acceleration)
	{
		printf("%s in %s on line: %d, Acceleration: expected %d but was %d\n", file, function, line, expected->Acceleration, p.Rte_A_accYDueToBankAngle_AccYDueToBankAngle.par.Acceleration);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_A_accYDueToBankAngle_AccYDueToBankAngle.par.Acceleration == expected->Acceleration);
}

void _stubs_check_LongMotionDirection_LongMotionDirection(LongMotionDirection_sg_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_LongMotionDirection_LongMotionDirection.par.LongMotionDirection != expected->LongMotionDirection)
	{
		printf("%s in %s on line: %d, LongMotionDirection: expected %d but was %d\n", file, function, line, expected->LongMotionDirection, p.Rte_LongMotionDirection_LongMotionDirection.par.LongMotionDirection);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_LongMotionDirection_LongMotionDirection.par.LongMotionDirection == expected->LongMotionDirection);
}

void _stubs_check_LongMotionDirectionQuality_LongMotionDirectionQuality(LongMotionDirectionQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_LongMotionDirectionQuality_LongMotionDirectionQuality.par.LongMotDirQuality != expected->LongMotDirQuality)
	{
		printf("%s in %s on line: %d, LongMotDirQuality: expected %d but was %d\n", file, function, line, expected->LongMotDirQuality, p.Rte_LongMotionDirectionQuality_LongMotionDirectionQuality.par.LongMotDirQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_LongMotionDirectionQuality_LongMotionDirectionQuality.par.LongMotDirQuality == expected->LongMotDirQuality);
}

void _stubs_check_LongMotionDirection_ErrorStatus_LongMotionDirection_ErrorStatus(LongMotionDirErrorSts_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_LongMotionDirection_ErrorStatus_LongMotionDirection_ErrorStatus.par.LongMotionDirErrorSts != expected->LongMotionDirErrorSts)
	{
		printf("%s in %s on line: %d, LongMotionDirErrorSts: expected %d but was %d\n", file, function, line, expected->LongMotionDirErrorSts, p.Rte_LongMotionDirection_ErrorStatus_LongMotionDirection_ErrorStatus.par.LongMotionDirErrorSts);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_LongMotionDirection_ErrorStatus_LongMotionDirection_ErrorStatus.par.LongMotionDirErrorSts == expected->LongMotionDirErrorSts);
}

void _stubs_check_D_nonlinearSteeringRatio_NonlinearSteeringRatio(SteeringRatio_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_D_nonlinearSteeringRatio_NonlinearSteeringRatio.par.SteeringRatio != expected->SteeringRatio)
	{
		printf("%s in %s on line: %d, SteeringRatio: expected %d but was %d\n", file, function, line, expected->SteeringRatio, p.Rte_D_nonlinearSteeringRatio_NonlinearSteeringRatio.par.SteeringRatio);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_D_nonlinearSteeringRatio_NonlinearSteeringRatio.par.SteeringRatio == expected->SteeringRatio);
}

void _stubs_check_E_spdXRefPointQly_SpdXRefPointQly(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_spdXRefPointQly_SpdXRefPointQly.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_spdXRefPointQly_SpdXRefPointQly.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_spdXRefPointQly_SpdXRefPointQly.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_spdYRefPointQly_SpdYRefPointQly(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_spdYRefPointQly_SpdYRefPointQly.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_spdYRefPointQly_SpdYRefPointQly.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_spdYRefPointQly_SpdYRefPointQly.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_accXRefPointQly_AccXRefPointQly(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_accXRefPointQly_AccXRefPointQly.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_accXRefPointQly_AccXRefPointQly.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_accXRefPointQly_AccXRefPointQly.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_accYRefPointQly_AccYRefPointQly(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_accYRefPointQly_AccYRefPointQly.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_accYRefPointQly_AccYRefPointQly.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_accYRefPointQly_AccYRefPointQly.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_yawRateRearAxleQly_YawRateRearAxleQly(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_yawRateRearAxleQly_YawRateRearAxleQly.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_yawRateRearAxleQly_YawRateRearAxleQly.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_yawRateRearAxleQly_YawRateRearAxleQly.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_yawAccRearAxleQly_YawAccRearAxleQly(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_yawAccRearAxleQly_YawAccRearAxleQly.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_yawAccRearAxleQly_YawAccRearAxleQly.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_yawAccRearAxleQly_YawAccRearAxleQly.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_sideslipRefPointQly_SideslipRefPointQly(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_sideslipRefPointQly_SideslipRefPointQly.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_sideslipRefPointQly_SideslipRefPointQly.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_sideslipRefPointQly_SideslipRefPointQly.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_roadWheelAngleQly_RoadWheelAngleQly(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_roadWheelAngleQly_RoadWheelAngleQly.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_roadWheelAngleQly_RoadWheelAngleQly.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_roadWheelAngleQly_RoadWheelAngleQly.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_crvtPathRefPointQly_CrvtPathRefPointQly(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_crvtPathRefPointQly_CrvtPathRefPointQly.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_crvtPathRefPointQly_CrvtPathRefPointQly.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_crvtPathRefPointQly_CrvtPathRefPointQly.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_equivalentRearAxlePositionQly_EquivalentRearAxlePositionQly(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_equivalentRearAxlePositionQly_EquivalentRearAxlePositionQly.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_equivalentRearAxlePositionQly_EquivalentRearAxlePositionQly.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_equivalentRearAxlePositionQly_EquivalentRearAxlePositionQly.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_V_spdYRefPoint_SpdYRefPoint(Speed_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_V_spdYRefPoint_SpdYRefPoint.par.Speed != expected->Speed)
	{
		printf("%s in %s on line: %d, Speed: expected %d but was %d\n", file, function, line, expected->Speed, p.Rte_V_spdYRefPoint_SpdYRefPoint.par.Speed);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_V_spdYRefPoint_SpdYRefPoint.par.Speed == expected->Speed);
}

void _stubs_check_V_spdAtWhl_Ax1L_V_spdAtWhl_Ax1L(V_spdAtWhl_Ax1L_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_V_spdAtWhl_Ax1L_V_spdAtWhl_Ax1L.par.V_spdAtWhl_Ax1 != expected->V_spdAtWhl_Ax1)
	{
		printf("%s in %s on line: %d, V_spdAtWhl_Ax1: expected %d but was %d\n", file, function, line, expected->V_spdAtWhl_Ax1, p.Rte_V_spdAtWhl_Ax1L_V_spdAtWhl_Ax1L.par.V_spdAtWhl_Ax1);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_V_spdAtWhl_Ax1L_V_spdAtWhl_Ax1L.par.V_spdAtWhl_Ax1 == expected->V_spdAtWhl_Ax1);
}

void _stubs_check_V_spdAtWhl_Ax1R_V_spdAtWhl_Ax1R(V_spdAtWhl_Ax1R_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_V_spdAtWhl_Ax1R_V_spdAtWhl_Ax1R.par.V_spdAtWhl_Ax1R != expected->V_spdAtWhl_Ax1R)
	{
		printf("%s in %s on line: %d, V_spdAtWhl_Ax1R: expected %d but was %d\n", file, function, line, expected->V_spdAtWhl_Ax1R, p.Rte_V_spdAtWhl_Ax1R_V_spdAtWhl_Ax1R.par.V_spdAtWhl_Ax1R);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_V_spdAtWhl_Ax1R_V_spdAtWhl_Ax1R.par.V_spdAtWhl_Ax1R == expected->V_spdAtWhl_Ax1R);
}

void _stubs_check_V_spdAtWhl_Ax2L_V_spdAtWhl_Ax2L(V_spdAtWhl_Ax2L_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_V_spdAtWhl_Ax2L_V_spdAtWhl_Ax2L.par.V_spdAtWhl_Ax2L != expected->V_spdAtWhl_Ax2L)
	{
		printf("%s in %s on line: %d, V_spdAtWhl_Ax2L: expected %d but was %d\n", file, function, line, expected->V_spdAtWhl_Ax2L, p.Rte_V_spdAtWhl_Ax2L_V_spdAtWhl_Ax2L.par.V_spdAtWhl_Ax2L);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_V_spdAtWhl_Ax2L_V_spdAtWhl_Ax2L.par.V_spdAtWhl_Ax2L == expected->V_spdAtWhl_Ax2L);
}

void _stubs_check_V_spdAtWhl_Ax2R_V_spdAtWhl_Ax2R(V_spdAtWhl_Ax2R_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_V_spdAtWhl_Ax2R_V_spdAtWhl_Ax2R.par.V_spdAtWhl_Ax2R != expected->V_spdAtWhl_Ax2R)
	{
		printf("%s in %s on line: %d, V_spdAtWhl_Ax2R: expected %d but was %d\n", file, function, line, expected->V_spdAtWhl_Ax2R, p.Rte_V_spdAtWhl_Ax2R_V_spdAtWhl_Ax2R.par.V_spdAtWhl_Ax2R);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_V_spdAtWhl_Ax2R_V_spdAtWhl_Ax2R.par.V_spdAtWhl_Ax2R == expected->V_spdAtWhl_Ax2R);
}

void _stubs_check_V_spdAtWhl_Ax3L_V_spdAtWhl_Ax3L(V_spdAtWhl_Ax3L_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_V_spdAtWhl_Ax3L_V_spdAtWhl_Ax3L.par.V_spdAtWhl_Ax3L != expected->V_spdAtWhl_Ax3L)
	{
		printf("%s in %s on line: %d, V_spdAtWhl_Ax3L: expected %d but was %d\n", file, function, line, expected->V_spdAtWhl_Ax3L, p.Rte_V_spdAtWhl_Ax3L_V_spdAtWhl_Ax3L.par.V_spdAtWhl_Ax3L);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_V_spdAtWhl_Ax3L_V_spdAtWhl_Ax3L.par.V_spdAtWhl_Ax3L == expected->V_spdAtWhl_Ax3L);
}

void _stubs_check_V_spdAtWhl_Ax3R_V_spdAtWhl_Ax3R(V_spdAtWhl_Ax3R_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_V_spdAtWhl_Ax3R_V_spdAtWhl_Ax3R.par.V_spdAtWhl_Ax3R != expected->V_spdAtWhl_Ax3R)
	{
		printf("%s in %s on line: %d, V_spdAtWhl_Ax3R: expected %d but was %d\n", file, function, line, expected->V_spdAtWhl_Ax3R, p.Rte_V_spdAtWhl_Ax3R_V_spdAtWhl_Ax3R.par.V_spdAtWhl_Ax3R);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_V_spdAtWhl_Ax3R_V_spdAtWhl_Ax3R.par.V_spdAtWhl_Ax3R == expected->V_spdAtWhl_Ax3R);
}

void _stubs_check_V_spdAtWhl_Ax4L_V_spdAtWhl_Ax4L(V_spdAtWhl_Ax4L_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_V_spdAtWhl_Ax4L_V_spdAtWhl_Ax4L.par.V_spdAtWhl_Ax4L != expected->V_spdAtWhl_Ax4L)
	{
		printf("%s in %s on line: %d, V_spdAtWhl_Ax4L: expected %d but was %d\n", file, function, line, expected->V_spdAtWhl_Ax4L, p.Rte_V_spdAtWhl_Ax4L_V_spdAtWhl_Ax4L.par.V_spdAtWhl_Ax4L);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_V_spdAtWhl_Ax4L_V_spdAtWhl_Ax4L.par.V_spdAtWhl_Ax4L == expected->V_spdAtWhl_Ax4L);
}

void _stubs_check_V_spdAtWhl_Ax4R_V_spdAtWhl_Ax4R(V_spdAtWhl_Ax4R_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_V_spdAtWhl_Ax4R_V_spdAtWhl_Ax4R.par.V_spdAtWhl_Ax4R != expected->V_spdAtWhl_Ax4R)
	{
		printf("%s in %s on line: %d, V_spdAtWhl_Ax4R: expected %d but was %d\n", file, function, line, expected->V_spdAtWhl_Ax4R, p.Rte_V_spdAtWhl_Ax4R_V_spdAtWhl_Ax4R.par.V_spdAtWhl_Ax4R);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_V_spdAtWhl_Ax4R_V_spdAtWhl_Ax4R.par.V_spdAtWhl_Ax4R == expected->V_spdAtWhl_Ax4R);
}

void _stubs_check_V_spdAtWhl_Ax5L_V_spdAtWhl_Ax5L(V_spdAtWhl_Ax5L_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_V_spdAtWhl_Ax5L_V_spdAtWhl_Ax5L.par.V_spdAtWhl_Ax5L != expected->V_spdAtWhl_Ax5L)
	{
		printf("%s in %s on line: %d, V_spdAtWhl_Ax5L: expected %d but was %d\n", file, function, line, expected->V_spdAtWhl_Ax5L, p.Rte_V_spdAtWhl_Ax5L_V_spdAtWhl_Ax5L.par.V_spdAtWhl_Ax5L);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_V_spdAtWhl_Ax5L_V_spdAtWhl_Ax5L.par.V_spdAtWhl_Ax5L == expected->V_spdAtWhl_Ax5L);
}

void _stubs_check_V_spdAtWhl_Ax5R_V_spdAtWhl_Ax5R(V_spdAtWhl_Ax5R_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_V_spdAtWhl_Ax5R_V_spdAtWhl_Ax5R.par.V_spdAtWhl_Ax5R != expected->V_spdAtWhl_Ax5R)
	{
		printf("%s in %s on line: %d, V_spdAtWhl_Ax5R: expected %d but was %d\n", file, function, line, expected->V_spdAtWhl_Ax5R, p.Rte_V_spdAtWhl_Ax5R_V_spdAtWhl_Ax5R.par.V_spdAtWhl_Ax5R);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_V_spdAtWhl_Ax5R_V_spdAtWhl_Ax5R.par.V_spdAtWhl_Ax5R == expected->V_spdAtWhl_Ax5R);
}

void _stubs_check_E_spdAtWhlQly_Ax1L_E_spdAtWhlQly_Ax1L(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_spdAtWhlQly_Ax1L_E_spdAtWhlQly_Ax1L.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_spdAtWhlQly_Ax1L_E_spdAtWhlQly_Ax1L.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_spdAtWhlQly_Ax1L_E_spdAtWhlQly_Ax1L.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_spdAtWhlQly_Ax1R_E_spdAtWhlQly_Ax1R(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_spdAtWhlQly_Ax1R_E_spdAtWhlQly_Ax1R.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_spdAtWhlQly_Ax1R_E_spdAtWhlQly_Ax1R.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_spdAtWhlQly_Ax1R_E_spdAtWhlQly_Ax1R.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_spdAtWhlQly_Ax2L_E_spdAtWhlQly_Ax2L(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_spdAtWhlQly_Ax2L_E_spdAtWhlQly_Ax2L.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_spdAtWhlQly_Ax2L_E_spdAtWhlQly_Ax2L.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_spdAtWhlQly_Ax2L_E_spdAtWhlQly_Ax2L.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_spdAtWhlQly_Ax2R_E_spdAtWhlQly_Ax2R(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_spdAtWhlQly_Ax2R_E_spdAtWhlQly_Ax2R.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_spdAtWhlQly_Ax2R_E_spdAtWhlQly_Ax2R.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_spdAtWhlQly_Ax2R_E_spdAtWhlQly_Ax2R.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_spdAtWhlQly_Ax3L_E_spdAtWhlQly_Ax3L(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_spdAtWhlQly_Ax3L_E_spdAtWhlQly_Ax3L.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_spdAtWhlQly_Ax3L_E_spdAtWhlQly_Ax3L.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_spdAtWhlQly_Ax3L_E_spdAtWhlQly_Ax3L.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_spdAtWhlQly_Ax3R_E_spdAtWhlQly_Ax3R(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_spdAtWhlQly_Ax3R_E_spdAtWhlQly_Ax3R.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_spdAtWhlQly_Ax3R_E_spdAtWhlQly_Ax3R.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_spdAtWhlQly_Ax3R_E_spdAtWhlQly_Ax3R.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_spdAtWhlQly_Ax4L_E_spdAtWhlQly_Ax4L(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_spdAtWhlQly_Ax4L_E_spdAtWhlQly_Ax4L.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_spdAtWhlQly_Ax4L_E_spdAtWhlQly_Ax4L.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_spdAtWhlQly_Ax4L_E_spdAtWhlQly_Ax4L.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_spdAtWhlQly_Ax4R_E_spdAtWhlQly_Ax4R(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_spdAtWhlQly_Ax4R_E_spdAtWhlQly_Ax4R.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_spdAtWhlQly_Ax4R_E_spdAtWhlQly_Ax4R.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_spdAtWhlQly_Ax4R_E_spdAtWhlQly_Ax4R.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_spdAtWhlQly_Ax5R_E_spdAtWhlQly_Ax5R(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_spdAtWhlQly_Ax5R_E_spdAtWhlQly_Ax5R.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_spdAtWhlQly_Ax5R_E_spdAtWhlQly_Ax5R.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_spdAtWhlQly_Ax5R_E_spdAtWhlQly_Ax5R.par.SignalQuality == expected->SignalQuality);
}

void _stubs_check_E_spdAtWhlQly_Ax5L_E_spdAtWhlQly_Ax5L(SignalQuality_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_E_spdAtWhlQly_Ax5L_E_spdAtWhlQly_Ax5L.par.SignalQuality != expected->SignalQuality)
	{
		printf("%s in %s on line: %d, SignalQuality: expected %d but was %d\n", file, function, line, expected->SignalQuality, p.Rte_E_spdAtWhlQly_Ax5L_E_spdAtWhlQly_Ax5L.par.SignalQuality);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_E_spdAtWhlQly_Ax5L_E_spdAtWhlQly_Ax5L.par.SignalQuality == expected->SignalQuality);
}

