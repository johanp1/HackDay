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

SEWS_D_precLongAccMeas_P10VW_T Rte_Prm_P10VW_D_precLongAccMeas_v()
{
	return c.P10VW_D_precLongAccMeas;
}

SEWS_SelfSteeredTagAxleThreshSpeed_P1AK9_T Rte_Prm_P1AK9_SelfSteeredTagAxleThreshSpeed_v()
{
	return c.P1AK9_SelfSteeredTagAxleThreshSpeed;
}

SEWS_D_lowSpdSnsrSelnLatAScaFac_X1C5B_T Rte_Prm_X1C5B_D_lowSpdSnsrSelnLatAScaFac_v()
{
	return c.X1C5B_D_lowSpdSnsrSelnLatAScaFac;
}

SEWS_D_FltHndlgIndirPrimSigFltScaFac_X1C6U_T Rte_Prm_X1C6U_D_FltHndlgIndirPrimSigFltScaFac_v()
{
	return c.X1C6U_D_FltHndlgIndirPrimSigFltScaFac;
}

SEWS_ConfigAxle_4_axle_load_max_P1A8I_T Rte_Prm_P1A8I_ConfigAxle_4_axle_load_max_v()
{
	return c.P1A8I_ConfigAxle_4_axle_load_max;
}

SEWS_D_precYawJerkInput_P10VT_T Rte_Prm_P10VT_D_precYawJerkInput_v()
{
	return c.P10VT_D_precYawJerkInput;
}

SEWS_ConfigAxle_4_p_thres_P1A8A_T Rte_Prm_P1A8A_ConfigAxle_4_p_thres_v()
{
	return c.P1A8A_ConfigAxle_4_p_thres;
}

SEWS_D_FltHndlgPrimSigFltScaFac_X1C68_T Rte_Prm_X1C68_D_FltHndlgPrimSigFltScaFac_v()
{
	return c.X1C68_D_FltHndlgPrimSigFltScaFac;
}

SEWS_ConfigAxle_1_axle_type_liftable_P1A59_T Rte_Prm_P1A59_ConfigAxle_1_axle_type_liftable_v()
{
	return c.P1A59_ConfigAxle_1_axle_type_liftable;
}

SEWS_ConfigAxle_2_wh_rollingcircu_P1A62_T Rte_Prm_P1A62_ConfigAxle_2_wh_rollingcircu_v()
{
	return c.P1A62_ConfigAxle_2_wh_rollingcircu;
}

SEWS_ConfigAxle_4_axle_type_steered_P1A71_T Rte_Prm_P1A71_ConfigAxle_4_axle_type_steered_v()
{
	return c.P1A71_ConfigAxle_4_axle_type_steered;
}

SEWS_T_interventionNoTrustTime_X1C60_T Rte_Prm_X1C60_T_interventionNoTrustTime_v()
{
	return c.X1C60_T_interventionNoTrustTime;
}

SEWS_SteeringRatio_P1BGV_T Rte_Prm_P1BGV_SteeringRatio_v()
{
	return c.P1BGV_SteeringRatio;
}

SEWS_VehicleType_P1L1L_T Rte_Prm_P1L1L_VehicleType_v()
{
	return c.P1L1L_VehicleType;
}

SEWS_ConfigAxle_2_axle_type_liftable_P1A6U_T Rte_Prm_P1A6U_ConfigAxle_2_axle_type_liftable_v()
{
	return c.P1A6U_ConfigAxle_2_axle_type_liftable;
}

SEWS_ConfigAxle_3_wh_rollingcircu_P1A7N_T Rte_Prm_P1A7N_ConfigAxle_3_wh_rollingcircu_v()
{
	return c.P1A7N_ConfigAxle_3_wh_rollingcircu;
}

SEWS_Tq_minEngineWheelTorque_X1C8Y_T Rte_Prm_X1C8Y_Tq_minEngineWheelTorque_v()
{
	return c.X1C8Y_Tq_minEngineWheelTorque;
}

SEWS_D_lowSpdSnsrSelnWhlSpdScaFac_X1C5E_T Rte_Prm_X1C5E_D_lowSpdSnsrSelnWhlSpdScaFac_v()
{
	return c.X1C5E_D_lowSpdSnsrSelnWhlSpdScaFac;
}

SEWS_D_normSlipStfnAxle5_P10WG_T Rte_Prm_P10WG_D_normSlipStfnAxle5_v()
{
	return c.P10WG_D_normSlipStfnAxle5;
}

SEWS_T_absAsrTurnOffDly_X1DCK_T Rte_Prm_X1DCK_T_absAsrTurnOffDly_v()
{
	return c.X1DCK_T_absAsrTurnOffDly;
}

SEWS_M_Axle5SuspVertLoads_P10W2_a_T* Rte_Prm_P10W2_M_Axle5SuspVertLoads_v()
{
	return &c.P10W2_M_Axle5SuspVertLoads;
}

SEWS_ConfigAxle_2_axle_load_max_P1A7C_T Rte_Prm_P1A7C_ConfigAxle_2_axle_load_max_v()
{
	return c.P1A7C_ConfigAxle_2_axle_load_max;
}

SEWS_M_Axle1SuspVertLoads_P10WU_a_T* Rte_Prm_P10WU_M_Axle1SuspVertLoads_v()
{
	return &c.P10WU_M_Axle1SuspVertLoads;
}

SEWS_ConfigAxle_5_axle_type_liftable_P1A8L_T Rte_Prm_P1A8L_ConfigAxle_5_axle_type_liftable_v()
{
	return c.P1A8L_ConfigAxle_5_axle_type_liftable;
}

SEWS_Frq_lowSpdSnsrSelnTqFilFrq_X1C48_T Rte_Prm_X1C48_Frq_lowSpdSnsrSelnTqFilFrq_v()
{
	return c.X1C48_Frq_lowSpdSnsrSelnTqFilFrq;
}

SEWS_ConfigAxle_1_p_thres_P1A6J_T Rte_Prm_P1A6J_ConfigAxle_1_p_thres_v()
{
	return c.P1A6J_ConfigAxle_1_p_thres;
}

SEWS_ConfigAxle_1_axle_load_max_P1A6R_T Rte_Prm_P1A6R_ConfigAxle_1_axle_load_max_v()
{
	return c.P1A6R_ConfigAxle_1_axle_load_max;
}

SEWS_D_normSlipStfnAxle2_P10WD_T Rte_Prm_P10WD_D_normSlipStfnAxle2_v()
{
	return c.P10WD_D_normSlipStfnAxle2;
}

SEWS_ConfigAxle_5_axle_load_max_P1A83_T Rte_Prm_P1A83_ConfigAxle_5_axle_load_max_v()
{
	return c.P1A83_ConfigAxle_5_axle_load_max;
}

SEWS_FAxleContactPatchOutside2OutsideDist_P1KJ7_T Rte_Prm_P1KJ7_FAxleContactPatchOutside2OutsideDist_v()
{
	return c.P1KJ7_FAxleContactPatchOutside2OutsideDist;
}

SEWS_RearAxleArrangement_P1CSG_T Rte_Prm_P1CSG_RearAxleArrangement_v()
{
	return c.P1CSG_RearAxleArrangement;
}

SEWS_ConfigAxle_3_brake_factor_P1A7Q_T Rte_Prm_P1A7Q_ConfigAxle_3_brake_factor_v()
{
	return c.P1A7Q_ConfigAxle_3_brake_factor;
}

SEWS_T_absAsrRstDelayTime_X1DU3_T Rte_Prm_X1DU3_T_absAsrRstDelayTime_v()
{
	return c.X1DU3_T_absAsrRstDelayTime;
}

SEWS_VehicleTargetGeneratorSpeedLimits1_P1B8U_T Rte_Prm_P1B8U_VehicleTargetGeneratorSpeedLimits1_v()
{
	return c.P1B8U_VehicleTargetGeneratorSpeedLimits1;
}

boolean Rte_Prm_X1BWH_YawRateMonitoringActivation_v()
{
	return c.X1BWH_YawRateMonitoringActivation;
}

SEWS_Stfn_Axle5SuspVertStfns_P10W3_a_T* Rte_Prm_P10W3_Stfn_Axle5SuspVertStfns_v()
{
	return &c.P10W3_Stfn_Axle5SuspVertStfns;
}

boolean Rte_Prm_X1C4J_B_enaSlipCmp_v()
{
	return c.X1C4J_B_enaSlipCmp;
}

SEWS_Stfn_Axle2SuspVertStfns_P10WX_a_T* Rte_Prm_P10WX_Stfn_Axle2SuspVertStfns_v()
{
	return &c.P10WX_Stfn_Axle2SuspVertStfns;
}

SEWS_D_precTrsmOutpShaftSpdMeas_X1C3K_T Rte_Prm_X1C3K_D_precTrsmOutpShaftSpdMeas_v()
{
	return c.X1C3K_D_precTrsmOutpShaftSpdMeas;
}

SEWS_ConfigAxle_3_axle_type_liftable_P1A7F_T Rte_Prm_P1A7F_ConfigAxle_3_axle_type_liftable_v()
{
	return c.P1A7F_ConfigAxle_3_axle_type_liftable;
}

SEWS_ConfigAxle_5_axle_type_steered_P1A8M_T Rte_Prm_P1A8M_ConfigAxle_5_axle_type_steered_v()
{
	return c.P1A8M_ConfigAxle_5_axle_type_steered;
}

SEWS_V_mtnDetnThdSpd_X1C9S_T Rte_Prm_X1C9S_V_mtnDetnThdSpd_v()
{
	return c.X1C9S_V_mtnDetnThdSpd;
}

SEWS_A_mtnDetnThdLongAcc_X1DBJ_T Rte_Prm_X1DBJ_A_mtnDetnThdLongAcc_v()
{
	return c.X1DBJ_A_mtnDetnThdLongAcc;
}

SEWS_D_precLongVelRateInit_X1C3E_T Rte_Prm_X1C3E_D_precLongVelRateInit_v()
{
	return c.X1C3E_D_precLongVelRateInit;
}

SEWS_BrandType_P1AFC_T Rte_Prm_P1AFC_BrandType_v()
{
	return c.P1AFC_BrandType;
}

SEWS_Frq_lowSpdSnsrSelnSpdFilFrq_X1C49_T Rte_Prm_X1C49_Frq_lowSpdSnsrSelnSpdFilFrq_v()
{
	return c.X1C49_Frq_lowSpdSnsrSelnSpdFilFrq;
}

SEWS_SteeringRatioRight2_P1BGZ_T Rte_Prm_P1BGZ_SteeringRatioRight2_v()
{
	return c.P1BGZ_SteeringRatioRight2;
}

boolean Rte_Prm_X1DCG_B_enaAbsAsrDetn_v()
{
	return c.X1DCG_B_enaAbsAsrDetn;
}

SEWS_V_lowSpdSnsrSelnSpdThldUp_P10V2_T Rte_Prm_P10V2_V_lowSpdSnsrSelnSpdThldUp_v()
{
	return c.P10V2_V_lowSpdSnsrSelnSpdThldUp;
}

SEWS_D_normSlipStfnAxle3_P10WE_T Rte_Prm_P10WE_D_normSlipStfnAxle3_v()
{
	return c.P10WE_D_normSlipStfnAxle3;
}

SEWS_DistRA1ToRA2_P1CNH_T Rte_Prm_P1CNH_DistRA1ToRA2_v()
{
	return c.P1CNH_DistRA1ToRA2;
}

SEWS_D_lowSpdSnsrSelnYawRateScaFac_X1C5C_T Rte_Prm_X1C5C_D_lowSpdSnsrSelnYawRateScaFac_v()
{
	return c.X1C5C_D_lowSpdSnsrSelnYawRateScaFac;
}

SEWS_D_absTracCompLgtAScaFac_X1C63_T Rte_Prm_X1C63_D_absTracCompLgtAScaFac_v()
{
	return c.X1C63_D_absTracCompLgtAScaFac;
}

SEWS_D_precLatJerkDueToBankAngleInput_P10VU_T Rte_Prm_P10VU_D_precLatJerkDueToBankAngleInput_v()
{
	return c.P10VU_D_precLatJerkDueToBankAngleInput;
}

SEWS_D_FltHndlgIndirAltvSigFltScaFac_X1C6V_T Rte_Prm_X1C6V_D_FltHndlgIndirAltvSigFltScaFac_v()
{
	return c.X1C6V_D_FltHndlgIndirAltvSigFltScaFac;
}

SEWS_ConfigAxle_2_axle_load_min_P1A7B_T Rte_Prm_P1A7B_ConfigAxle_2_axle_load_min_v()
{
	return c.P1A7B_ConfigAxle_2_axle_load_min;
}

SEWS_M_Axle4SuspVertLoads_P10W0_a_T* Rte_Prm_P10W0_M_Axle4SuspVertLoads_v()
{
	return &c.P10W0_M_Axle4SuspVertLoads;
}

SEWS_L_trackWidthDrivenAxle_X1C3A_T Rte_Prm_X1C3A_L_trackWidthDrivenAxle_v()
{
	return c.X1C3A_L_trackWidthDrivenAxle;
}

SEWS_ConfigAxle_1_axle_type_steered_P1A6A_T Rte_Prm_P1A6A_ConfigAxle_1_axle_type_steered_v()
{
	return c.P1A6A_ConfigAxle_1_axle_type_steered;
}

SEWS_ConfigAxle_2_brake_factor_P1A65_T Rte_Prm_P1A65_ConfigAxle_2_brake_factor_v()
{
	return c.P1A65_ConfigAxle_2_brake_factor;
}

SEWS_D_maxWheelSpeedTrustFac_vec_X1C69_a_T* Rte_Prm_X1C69_D_maxWheelSpeedTrustFac_vec_v()
{
	return &c.X1C69_D_maxWheelSpeedTrustFac_vec;
}

SEWS_Tq_lowSpdSnsrSelnTqThldUp_X1C46_T Rte_Prm_X1C46_Tq_lowSpdSnsrSelnTqThldUp_v()
{
	return c.X1C46_Tq_lowSpdSnsrSelnTqThldUp;
}

SEWS_ConfigAxle_3_axle_load_min_P1A7W_T Rte_Prm_P1A7W_ConfigAxle_3_axle_load_min_v()
{
	return c.P1A7W_ConfigAxle_3_axle_load_min;
}

SEWS_SteeringRatioLeft1_P1BGW_T Rte_Prm_P1BGW_SteeringRatioLeft1_v()
{
	return c.P1BGW_SteeringRatioLeft1;
}

SEWS_D_precWhlSpdMeas_X1C5P_T Rte_Prm_X1C5P_D_precWhlSpdMeas_v()
{
	return c.X1C5P_D_precWhlSpdMeas;
}

SEWS_ConfigAxle_2_axle_type_steered_P1A6V_T Rte_Prm_P1A6V_ConfigAxle_2_axle_type_steered_v()
{
	return c.P1A6V_ConfigAxle_2_axle_type_steered;
}

SEWS_T_zeroSpdFltrTurnOffDly_X1C5W_T Rte_Prm_X1C5W_T_zeroSpdFltrTurnOffDly_v()
{
	return c.X1C5W_T_zeroSpdFltrTurnOffDly;
}

SEWS_D_wheelSpeedTrustFac_vec_X1C8Z_a_T* Rte_Prm_X1C8Z_D_wheelSpeedTrustFac_vec_v()
{
	return &c.X1C8Z_D_wheelSpeedTrustFac_vec;
}

SEWS_DistRA2ToRA3_P1CNJ_T Rte_Prm_P1CNJ_DistRA2ToRA3_v()
{
	return c.P1CNJ_DistRA2ToRA3;
}

SEWS_L_imuToFrontAxle_P10WH_T Rte_Prm_P10WH_L_imuToFrontAxle_v()
{
	return c.P10WH_L_imuToFrontAxle;
}

SEWS_Stfn_Axle4SuspVertStfns_P10W1_a_T* Rte_Prm_P10W1_Stfn_Axle4SuspVertStfns_v()
{
	return &c.P10W1_Stfn_Axle4SuspVertStfns;
}

SEWS_ConfigAxle_4_wh_rollingcircu_P1A78_T Rte_Prm_P1A78_ConfigAxle_4_wh_rollingcircu_v()
{
	return c.P1A78_ConfigAxle_4_wh_rollingcircu;
}

SEWS_L_maxCogHeightFullyLaden_P10WS_T Rte_Prm_P10WS_L_maxCogHeightFullyLaden_v()
{
	return c.P10WS_L_maxCogHeightFullyLaden;
}

SEWS_E_EbsSwPackage_P1K5K_T Rte_Prm_P1K5K_E_EbsSwPackage_v()
{
	return c.P1K5K_E_EbsSwPackage;
}

boolean Rte_Prm_X1C4U_B_enaLowSpdSnsrSeln_v()
{
	return c.X1C4U_B_enaLowSpdSnsrSeln;
}

SEWS_Stfn_Axle1SuspVertStfns_P10WV_a_T* Rte_Prm_P10WV_Stfn_Axle1SuspVertStfns_v()
{
	return &c.P10WV_Stfn_Axle1SuspVertStfns;
}

SEWS_Tq_lowSpdSnsrSelnTqThldLo_X1C47_T Rte_Prm_X1C47_Tq_lowSpdSnsrSelnTqThldLo_v()
{
	return c.X1C47_Tq_lowSpdSnsrSelnTqThldLo;
}

SEWS_ConfigAxle_3_axle_load_max_P1A7X_T Rte_Prm_P1A7X_ConfigAxle_3_axle_load_max_v()
{
	return c.P1A7X_ConfigAxle_3_axle_load_max;
}

SEWS_ConfigAxle_1_brake_factor_P1A6K_T Rte_Prm_P1A6K_ConfigAxle_1_brake_factor_v()
{
	return c.P1A6K_ConfigAxle_1_brake_factor;
}

SEWS_T_mtnLowConfTolrTi_X1DCF_T Rte_Prm_X1DCF_T_mtnLowConfTolrTi_v()
{
	return c.X1DCF_T_mtnLowConfTolrTi;
}

SEWS_ConfigAxle_1_axle_load_min_P1A6Q_T Rte_Prm_P1A6Q_ConfigAxle_1_axle_load_min_v()
{
	return c.P1A6Q_ConfigAxle_1_axle_load_min;
}

SEWS_FrontAxleArrangement_P1CSH_T Rte_Prm_P1CSH_FrontAxleArrangement_v()
{
	return c.P1CSH_FrontAxleArrangement;
}

SEWS_ConfigAxle_5_axle_load_min_P1A82_T Rte_Prm_P1A82_ConfigAxle_5_axle_load_min_v()
{
	return c.P1A82_ConfigAxle_5_axle_load_min;
}

SEWS_D_precLatAccDueToBankAngleInit_X1DBH_T Rte_Prm_X1DBH_D_precLatAccDueToBankAngleInit_v()
{
	return c.X1DBH_D_precLatAccDueToBankAngleInit;
}

SEWS_D_precLatAccMeas_P10VX_T Rte_Prm_P10VX_D_precLatAccMeas_v()
{
	return c.P10VX_D_precLatAccMeas;
}

SEWS_D_FltHndlgAltvSigFltScaFac_X1C6T_T Rte_Prm_X1C6T_D_FltHndlgAltvSigFltScaFac_v()
{
	return c.X1C6T_D_FltHndlgAltvSigFltScaFac;
}

SEWS_E_BusAxleType_P11DU_T Rte_Prm_P11DU_E_BusAxleType_v()
{
	return c.P11DU_E_BusAxleType;
}

SEWS_VehicleTargetGeneratorSpeedLimits2_P1B8V_T Rte_Prm_P1B8V_VehicleTargetGeneratorSpeedLimits2_v()
{
	return c.P1B8V_VehicleTargetGeneratorSpeedLimits2;
}

SEWS_D_absTracCompLongJerkScaFac_X1DBQ_T Rte_Prm_X1DBQ_D_absTracCompLongJerkScaFac_v()
{
	return c.X1DBQ_D_absTracCompLongJerkScaFac;
}

SEWS_D_lowSpdSnsrSelnLgtAScaFac_X1C5A_T Rte_Prm_X1C5A_D_lowSpdSnsrSelnLgtAScaFac_v()
{
	return c.X1C5A_D_lowSpdSnsrSelnLgtAScaFac;
}

SEWS_T_interventionRampUpTime_X1C61_T Rte_Prm_X1C61_T_interventionRampUpTime_v()
{
	return c.X1C61_T_interventionRampUpTime;
}

SEWS_D_precLongJerkInput_P10VS_T Rte_Prm_P10VS_D_precLongJerkInput_v()
{
	return c.P10VS_D_precLongJerkInput;
}

SEWS_ConfigAxle_4_axle_load_min_P1A8H_T Rte_Prm_P1A8H_ConfigAxle_4_axle_load_min_v()
{
	return c.P1A8H_ConfigAxle_4_axle_load_min;
}

SEWS_DistFA1ToFA2_P1KME_T Rte_Prm_P1KME_DistFA1ToFA2_v()
{
	return c.P1KME_DistFA1ToFA2;
}

SEWS_D_absTracCompLatAScaFac_X1DBO_T Rte_Prm_X1DBO_D_absTracCompLatAScaFac_v()
{
	return c.X1DBO_D_absTracCompLatAScaFac;
}

SEWS_D_lowSpdSnsrSelnLgtJerkScaFacSpd_X1C5T_T Rte_Prm_X1C5T_D_lowSpdSnsrSelnLgtJerkScaFacSpd_v()
{
	return c.X1C5T_D_lowSpdSnsrSelnLgtJerkScaFacSpd;
}

SEWS_M_Axle3SuspVertLoads_P10WY_a_T* Rte_Prm_P10WY_M_Axle3SuspVertLoads_v()
{
	return &c.P10WY_M_Axle3SuspVertLoads;
}

SEWS_ConfigAxle_4_brake_factor_P1A8B_T Rte_Prm_P1A8B_ConfigAxle_4_brake_factor_v()
{
	return c.P1A8B_ConfigAxle_4_brake_factor;
}

boolean Rte_Prm_X1C8W_B_enaWheelDeselection_v()
{
	return c.X1C8W_B_enaWheelDeselection;
}

SEWS_T_absAsrDetnDelayTime_X1DU0_T Rte_Prm_X1DU0_T_absAsrDetnDelayTime_v()
{
	return c.X1DU0_T_absAsrDetnDelayTime;
}

SEWS_ConfigAxle_3_axle_type_steered_P1A7G_T Rte_Prm_P1A7G_ConfigAxle_3_axle_type_steered_v()
{
	return c.P1A7G_ConfigAxle_3_axle_type_steered;
}

SEWS_D_precYawRateInit_X1C3F_T Rte_Prm_X1C3F_D_precYawRateInit_v()
{
	return c.X1C3F_D_precYawRateInit;
}

SEWS_ConfigAxle_1_wh_rollingcircu_P1A6H_T Rte_Prm_P1A6H_ConfigAxle_1_wh_rollingcircu_v()
{
	return c.P1A6H_ConfigAxle_1_wh_rollingcircu;
}

SEWS_ConfigAxle_4_axle_type_liftable_P1A70_T Rte_Prm_P1A70_ConfigAxle_4_axle_type_liftable_v()
{
	return c.P1A70_ConfigAxle_4_axle_type_liftable;
}

SEWS_A_whlRateAbsAsrDetnThd_X1DCH_T Rte_Prm_X1DCH_A_whlRateAbsAsrDetnThd_v()
{
	return c.X1DCH_A_whlRateAbsAsrDetnThd;
}

SEWS_ConfigAxle_5_p_thres_P1A8V_T Rte_Prm_P1A8V_ConfigAxle_5_p_thres_v()
{
	return c.P1A8V_ConfigAxle_5_p_thres;
}

SEWS_ConfigAxle_3_p_thres_P1A7P_T Rte_Prm_P1A7P_ConfigAxle_3_p_thres_v()
{
	return c.P1A7P_ConfigAxle_3_p_thres;
}

SEWS_NetworkArchitecture_P1RPH_T Rte_Prm_P1RPH_NetworkArchitecture_v()
{
	return c.P1RPH_NetworkArchitecture;
}

SEWS_D_precYawRateMeas_P10VY_T Rte_Prm_P10VY_D_precYawRateMeas_v()
{
	return c.P10VY_D_precYawRateMeas;
}

SEWS_D_lowSpdSnsrSelnTrsmSpdScaFac_X1C5D_T Rte_Prm_X1C5D_D_lowSpdSnsrSelnTrsmSpdScaFac_v()
{
	return c.X1C5D_D_lowSpdSnsrSelnTrsmSpdScaFac;
}

SEWS_TagAxleFeatures_P1CSI_T Rte_Prm_P1CSI_TagAxleFeatures_v()
{
	return c.P1CSI_TagAxleFeatures;
}

SEWS_D_normSlipStfnAxle4_P10WF_T Rte_Prm_P10WF_D_normSlipStfnAxle4_v()
{
	return c.P10WF_D_normSlipStfnAxle4;
}

boolean Rte_Prm_X1C62_B_enaTracComp_v()
{
	return c.X1C62_B_enaTracComp;
}

SEWS_D_absTracCompYawRateScaFac_X1DBP_T Rte_Prm_X1DBP_D_absTracCompYawRateScaFac_v()
{
	return c.X1DBP_D_absTracCompYawRateScaFac;
}

SEWS_V_maxWheelSpeedTrustBreakPoints_vec_X1C7C_a_T* Rte_Prm_X1C7C_V_maxWheelSpeedTrustBreakPoints_vec_v()
{
	return &c.X1C7C_V_maxWheelSpeedTrustBreakPoints_vec;
}

SEWS_Frq_lowSpdSnsrSelnSpdFilFrq_X1C5U_T Rte_Prm_X1C5U_Frq_lowSpdSnsrSelnSpdFilFrq_v()
{
	return c.X1C5U_Frq_lowSpdSnsrSelnSpdFilFrq;
}

SEWS_Stfn_Axle3SuspVertStfns_P10WZ_a_T* Rte_Prm_P10WZ_Stfn_Axle3SuspVertStfns_v()
{
	return &c.P10WZ_Stfn_Axle3SuspVertStfns;
}

SEWS_L_trackWidthNonDrivenAxle_X1C29_T Rte_Prm_X1C29_L_trackWidthNonDrivenAxle_v()
{
	return c.X1C29_L_trackWidthNonDrivenAxle;
}

SEWS_Tq_minTotalBrakeTorque_X1C8X_T Rte_Prm_X1C8X_Tq_minTotalBrakeTorque_v()
{
	return c.X1C8X_Tq_minTotalBrakeTorque;
}

SEWS_D_precYawAccInit_X1C3G_T Rte_Prm_X1C3G_D_precYawAccInit_v()
{
	return c.X1C3G_D_precYawAccInit;
}

SEWS_ConfigAxle_2_p_thres_P1A64_T Rte_Prm_P1A64_ConfigAxle_2_p_thres_v()
{
	return c.P1A64_ConfigAxle_2_p_thres;
}

SEWS_Radar2FrontAxleDist_P1E5Z_T Rte_Prm_P1E5Z_Radar2FrontAxleDist_v()
{
	return c.P1E5Z_Radar2FrontAxleDist;
}

SEWS_ConfigAxle_5_brake_factor_P1A8W_T Rte_Prm_P1A8W_ConfigAxle_5_brake_factor_v()
{
	return c.P1A8W_ConfigAxle_5_brake_factor;
}

SEWS_D_normSlipStfnAxle1_P10WC_T Rte_Prm_P10WC_D_normSlipStfnAxle1_v()
{
	return c.P10WC_D_normSlipStfnAxle1;
}

SEWS_Frq_whlRateFilFrq_X1DCI_T Rte_Prm_X1DCI_Frq_whlRateFilFrq_v()
{
	return c.X1DCI_Frq_whlRateFilFrq;
}

SEWS_D_lowSpdSnsrSelnLgtJerkScaFacTrq_X1C5Q_T Rte_Prm_X1C5Q_D_lowSpdSnsrSelnLgtJerkScaFacTrq_v()
{
	return c.X1C5Q_D_lowSpdSnsrSelnLgtJerkScaFacTrq;
}

SEWS_L_minCogHeightUnladen_P10WR_T Rte_Prm_P10WR_L_minCogHeightUnladen_v()
{
	return c.P10WR_L_minCogHeightUnladen;
}

SEWS_V_speedDifferenceBreakPoints_vec_X1C80_a_T* Rte_Prm_X1C80_V_speedDifferenceBreakPoints_vec_v()
{
	return &c.X1C80_V_speedDifferenceBreakPoints_vec;
}

SEWS_EquivalentWheelbaseTurning_P1IJ3_T Rte_Prm_P1IJ3_EquivalentWheelbaseTurning_v()
{
	return c.P1IJ3_EquivalentWheelbaseTurning;
}

SEWS_A_whlRateAbsAsrRstThd_X1DCM_T Rte_Prm_X1DCM_A_whlRateAbsAsrRstThd_v()
{
	return c.X1DCM_A_whlRateAbsAsrRstThd;
}

SEWS_D_precLongVelInit_X1C3D_T Rte_Prm_X1C3D_D_precLongVelInit_v()
{
	return c.X1C3D_D_precLongVelInit;
}

SEWS_SelfSteeredTagAxleSpeedHysteresis_P1AT2_T Rte_Prm_P1AT2_SelfSteeredTagAxleSpeedHysteresis_v()
{
	return c.P1AT2_SelfSteeredTagAxleSpeedHysteresis;
}

SEWS_AgV_maxPitchRate_P10WT_T Rte_Prm_P10WT_AgV_maxPitchRate_v()
{
	return c.P10WT_AgV_maxPitchRate;
}

SEWS_M_Axle2SuspVertLoads_P10WW_a_T* Rte_Prm_P10WW_M_Axle2SuspVertLoads_v()
{
	return &c.P10WW_M_Axle2SuspVertLoads;
}

SEWS_SteeringRatioLeft2_P1BGX_T Rte_Prm_P1BGX_SteeringRatioLeft2_v()
{
	return c.P1BGX_SteeringRatioLeft2;
}

SEWS_V_mtnDetnHysSpd_X1C9T_T Rte_Prm_X1C9T_V_mtnDetnHysSpd_v()
{
	return c.X1C9T_V_mtnDetnHysSpd;
}

boolean Rte_Prm_X1C6Z_B_enaAbsComp_v()
{
	return c.X1C6Z_B_enaAbsComp;
}

SEWS_SteeringRatioRight1_P1BGY_T Rte_Prm_P1BGY_SteeringRatioRight1_v()
{
	return c.P1BGY_SteeringRatioRight1;
}

SEWS_V_lowSpdSnsrSelnSpdThldLo_P10V1_T Rte_Prm_P10V1_V_lowSpdSnsrSelnSpdThldLo_v()
{
	return c.P10V1_V_lowSpdSnsrSelnSpdThldLo;
}

SEWS_ConfigAxle_5_wh_rollingcircu_P1A8T_T Rte_Prm_P1A8T_ConfigAxle_5_wh_rollingcircu_v()
{
	return c.P1A8T_ConfigAxle_5_wh_rollingcircu;
}

boolean Rte_Prm_P1A0N_B_EspNotAvailable_v()
{
	return c.P1A0N_B_EspNotAvailable;
}

SEWS_WheelBase_P1AZQ_T Rte_Prm_P1AZQ_WheelBase_v()
{
	return c.P1AZQ_WheelBase;
}

SEWS_VehicleWidth_mm_P1E50_T Rte_Prm_P1E50_VehicleWidth_mm_v()
{
	return c.P1E50_VehicleWidth_mm;
}

SEWS_NoOfPulsesPerRevolution_P1M6I_T Rte_Prm_P1M6I_NoOfPulsesPerRevolution_v()
{
	return c.P1M6I_NoOfPulsesPerRevolution;
}

boolean Rte_Prm_P1C54_FactoryModeActive_v()
{
	return c.P1C54_FactoryModeActive;
}

