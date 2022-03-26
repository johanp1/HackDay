#define DISABLE_RTE_PTR2ARRAYBASETYPE_PASSING

#include "cunit_se_stubs.h"

StubSignals_Type p;

Std_ReturnType Rte_Read_ASREngineControlActive_ASREngineControlActive(PassiveActive2_T* par)
{
	*par = p.Rte_ASREngineControlActive_ASREngineControlActive.par;
	return p.Rte_ASREngineControlActive_ASREngineControlActive.ret;
}

Std_ReturnType Rte_Read_EngineSpeed_EngineSpeed(SpeedRpm16bit_T* par)
{
	*par = p.Rte_EngineSpeed_EngineSpeed.par;
	return p.Rte_EngineSpeed_EngineSpeed.ret;
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

Std_ReturnType Rte_Read_TransmissionShiftInProcess_TransmissionShiftInProcess(TransmissionShiftInProcess_T* par)
{
	*par = p.Rte_TransmissionShiftInProcess_TransmissionShiftInProcess.par;
	return p.Rte_TransmissionShiftInProcess_TransmissionShiftInProcess.ret;
}

Std_ReturnType Rte_Read_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged(DisengageEngage_T* par)
{
	*par = p.Rte_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged.par;
	return p.Rte_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged.ret;
}

Std_ReturnType Rte_Read_TransmissionCurrentGear_TransmissionCurrentGear(TransmissionGear_T* par)
{
	*par = p.Rte_TransmissionCurrentGear_TransmissionCurrentGear.par;
	return p.Rte_TransmissionCurrentGear_TransmissionCurrentGear.ret;
}

Std_ReturnType Rte_Read_ACC_SGO_Status_ACC_SGO_Status(ACC_SGO_Status_T* par)
{
	*par = p.Rte_ACC_SGO_Status_ACC_SGO_Status.par;
	return p.Rte_ACC_SGO_Status_ACC_SGO_Status.ret;
}

Std_ReturnType Rte_Read_RoadInclinationPerc_RoadInclinationPerc(RoadInclinationPerc_T* par)
{
	*par = p.Rte_RoadInclinationPerc_RoadInclinationPerc.par;
	return p.Rte_RoadInclinationPerc_RoadInclinationPerc.ret;
}

Std_ReturnType Rte_Read_ABSAxle1Active_ABSAxle1Active(OffOn_T* par)
{
	*par = p.Rte_ABSAxle1Active_ABSAxle1Active.par;
	return p.Rte_ABSAxle1Active_ABSAxle1Active.ret;
}

Std_ReturnType Rte_Read_ABSAxle2Active_ABSAxle2Active(OffOn_T* par)
{
	*par = p.Rte_ABSAxle2Active_ABSAxle2Active.par;
	return p.Rte_ABSAxle2Active_ABSAxle2Active.ret;
}

Std_ReturnType Rte_Read_ABSAxle3Active_ABSAxle3Active(OffOn_T* par)
{
	*par = p.Rte_ABSAxle3Active_ABSAxle3Active.par;
	return p.Rte_ABSAxle3Active_ABSAxle3Active.ret;
}

Std_ReturnType Rte_Read_ABSAxle4Active_ABSAxle4Active(OffOn_T* par)
{
	*par = p.Rte_ABSAxle4Active_ABSAxle4Active.par;
	return p.Rte_ABSAxle4Active_ABSAxle4Active.ret;
}

Std_ReturnType Rte_Read_ABSAxle5Active_ABSAxle5Active(OffOn_T* par)
{
	*par = p.Rte_ABSAxle5Active_ABSAxle5Active.par;
	return p.Rte_ABSAxle5Active_ABSAxle5Active.ret;
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

Std_ReturnType Rte_Read_FASFullyOperational_FASFullyOperational(FASFullyOperational_T* par)
{
	*par = p.Rte_FASFullyOperational_FASFullyOperational.par;
	return p.Rte_FASFullyOperational_FASFullyOperational.ret;
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

Std_ReturnType Rte_Read_FrontRoadWheelAngleEstimate_FrontRoadWheelAngleEstimate(RoadWheelAngle_T* par)
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

Std_ReturnType Rte_Read_PusherAxleLeftWheelSpeed_PusherAxleLeftWheelSpeed(Speed16bit_T* par)
{
	*par = p.Rte_PusherAxleLeftWheelSpeed_PusherAxleLeftWheelSpeed.par;
	return p.Rte_PusherAxleLeftWheelSpeed_PusherAxleLeftWheelSpeed.ret;
}

Std_ReturnType Rte_Read_PusherAxleLoad_AxleLoad(AxleLoad_T* par)
{
	*par = p.Rte_PusherAxleLoad_AxleLoad.par;
	return p.Rte_PusherAxleLoad_AxleLoad.ret;
}

Std_ReturnType Rte_Read_PusherAxleRightWheelSpeed_PusherAxleRightWheelSpeed(Speed16bit_T* par)
{
	*par = p.Rte_PusherAxleRightWheelSpeed_PusherAxleRightWheelSpeed.par;
	return p.Rte_PusherAxleRightWheelSpeed_PusherAxleRightWheelSpeed.ret;
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

Std_ReturnType Rte_Read_ScndFrAxleLeftWheelSpeed_ScndFrAxleLeftWheelSpeed(Speed16bit_T* par)
{
	*par = p.Rte_ScndFrAxleLeftWheelSpeed_ScndFrAxleLeftWheelSpeed.par;
	return p.Rte_ScndFrAxleLeftWheelSpeed_ScndFrAxleLeftWheelSpeed.ret;
}

Std_ReturnType Rte_Read_ScndFrAxleRightWheelSpeed_ScndFrAxleRightWheelSpeed(Speed16bit_T* par)
{
	*par = p.Rte_ScndFrAxleRightWheelSpeed_ScndFrAxleRightWheelSpeed.par;
	return p.Rte_ScndFrAxleRightWheelSpeed_ScndFrAxleRightWheelSpeed.ret;
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

Std_ReturnType Rte_Read_TagAxleLeftWheelSpeed_TagAxleLeftWheelSpeed(Speed16bit_T* par)
{
	*par = p.Rte_TagAxleLeftWheelSpeed_TagAxleLeftWheelSpeed.par;
	return p.Rte_TagAxleLeftWheelSpeed_TagAxleLeftWheelSpeed.ret;
}

Std_ReturnType Rte_Read_TagAxleLoad_AxleLoad(AxleLoad_T* par)
{
	*par = p.Rte_TagAxleLoad_AxleLoad.par;
	return p.Rte_TagAxleLoad_AxleLoad.ret;
}

Std_ReturnType Rte_Read_TagAxleRightWheelSpeed_TagAxleRightWheelSpeed(Speed16bit_T* par)
{
	*par = p.Rte_TagAxleRightWheelSpeed_TagAxleRightWheelSpeed.par;
	return p.Rte_TagAxleRightWheelSpeed_TagAxleRightWheelSpeed.ret;
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

Std_ReturnType Rte_Read_ScndRrDriveAxleLeftWheelSpeed_ScndRrDriveAxleLeftWheelSpeed(Speed16bit_T* par)
{
	*par = p.Rte_ScndRrDriveAxleLeftWheelSpeed_ScndRrDriveAxleLeftWheelSpeed.par;
	return p.Rte_ScndRrDriveAxleLeftWheelSpeed_ScndRrDriveAxleLeftWheelSpeed.ret;
}

Std_ReturnType Rte_Read_ScndRrDriveAxleRightWheelSpeed_ScndRrDriveAxleRightWheelSpeed(Speed16bit_T* par)
{
	*par = p.Rte_ScndRrDriveAxleRightWheelSpeed_ScndRrDriveAxleRightWheelSpeed.par;
	return p.Rte_ScndRrDriveAxleRightWheelSpeed_ScndRrDriveAxleRightWheelSpeed.ret;
}

Std_ReturnType Rte_Read_FrontAxleSpeed_FrontAxleSpeed(Speed16bit_T* par)
{
	*par = p.Rte_FrontAxleSpeed_FrontAxleSpeed.par;
	return p.Rte_FrontAxleSpeed_FrontAxleSpeed.ret;
}

Std_ReturnType Rte_Read_ABSFullyOperational_ABSFullyOperational(FullyOperational_T* par)
{
	*par = p.Rte_ABSFullyOperational_ABSFullyOperational.par;
	return p.Rte_ABSFullyOperational_ABSFullyOperational.ret;
}

Std_ReturnType Rte_Write_VehicleYawInertia_VehicleYawInertia(InertiaQ_T const* par)
{
	p.Rte_VehicleYawInertia_VehicleYawInertia.par = *par;
	return p.Rte_VehicleYawInertia_VehicleYawInertia.ret;
}

Std_ReturnType Rte_Write_VehicleRollInertia_VehicleRollInertia(InertiaQ_T const* par)
{
	p.Rte_VehicleRollInertia_VehicleRollInertia.par = *par;
	return p.Rte_VehicleRollInertia_VehicleRollInertia.ret;
}

Std_ReturnType Rte_Write_VehiclePitchInertia_VehiclePitchInertia(InertiaQ_T const* par)
{
	p.Rte_VehiclePitchInertia_VehiclePitchInertia.par = *par;
	return p.Rte_VehiclePitchInertia_VehiclePitchInertia.ret;
}

Std_ReturnType Rte_Write_RearAxleCurvature_RearAxleCurvature(AxleCurvature_T const* par)
{
	p.Rte_RearAxleCurvature_RearAxleCurvature.par = *par;
	return p.Rte_RearAxleCurvature_RearAxleCurvature.ret;
}

Std_ReturnType Rte_Write_SpeedOverGround_SpeedOverGround(SpeedQ_T const* par)
{
	p.Rte_SpeedOverGround_SpeedOverGround.par = *par;
	return p.Rte_SpeedOverGround_SpeedOverGround.ret;
}

Std_ReturnType Rte_Write_LongitudinalAccelerationQ_LongitudinalAccelerationQ(AccelerationQ_T const* par)
{
	p.Rte_LongitudinalAccelerationQ_LongitudinalAccelerationQ.par = *par;
	return p.Rte_LongitudinalAccelerationQ_LongitudinalAccelerationQ.ret;
}

Std_ReturnType Rte_Write_ArticulationAngle_ArticulationAngle(AngleQ_T const* par)
{
	p.Rte_ArticulationAngle_ArticulationAngle.par = *par;
	return p.Rte_ArticulationAngle_ArticulationAngle.ret;
}

Std_ReturnType Rte_Write_FrontAxleLoadQ_AxleLoadQ_I(LoadQ_T const* par)
{
	p.Rte_FrontAxleLoadQ_AxleLoadQ_I.par = *par;
	return p.Rte_FrontAxleLoadQ_AxleLoadQ_I.ret;
}

Std_ReturnType Rte_Write_PusherAxleLoadQ_AxleLoadQ_I(LoadQ_T const* par)
{
	p.Rte_PusherAxleLoadQ_AxleLoadQ_I.par = *par;
	return p.Rte_PusherAxleLoadQ_AxleLoadQ_I.ret;
}

Std_ReturnType Rte_Write_DriveAxleLoadQ_AxleLoadQ_I(LoadQ_T const* par)
{
	p.Rte_DriveAxleLoadQ_AxleLoadQ_I.par = *par;
	return p.Rte_DriveAxleLoadQ_AxleLoadQ_I.ret;
}

Std_ReturnType Rte_Write_TrailerAxleLoadQ_AxleLoadQ_I(LoadQ_T const* par)
{
	p.Rte_TrailerAxleLoadQ_AxleLoadQ_I.par = *par;
	return p.Rte_TrailerAxleLoadQ_AxleLoadQ_I.ret;
}

Std_ReturnType Rte_Write_RearAxleLifted_RearAxleLifted_I(LiftedQ_T const* par)
{
	p.Rte_RearAxleLifted_RearAxleLifted_I.par = *par;
	return p.Rte_RearAxleLifted_RearAxleLifted_I.ret;
}

Std_ReturnType Rte_Write_MotionState_MotionState_I(MotionStateQ_T const* par)
{
	p.Rte_MotionState_MotionState_I.par = *par;
	return p.Rte_MotionState_MotionState_I.ret;
}

Std_ReturnType Rte_Write_TrailerConnected_TrailerConnected(TrailerConnectedQ_T const* par)
{
	p.Rte_TrailerConnected_TrailerConnected.par = *par;
	return p.Rte_TrailerConnected_TrailerConnected.ret;
}

Std_ReturnType Rte_Write_VehicleStandstill_VehicleStandstill(StandstillQ_T const* par)
{
	p.Rte_VehicleStandstill_VehicleStandstill.par = *par;
	return p.Rte_VehicleStandstill_VehicleStandstill.ret;
}

Std_ReturnType Rte_Write_VehicleStructureSts_VehicleStructureSts(VehicleStructureSts_T const* par)
{
	p.Rte_VehicleStructureSts_VehicleStructureSts.par = *par;
	return p.Rte_VehicleStructureSts_VehicleStructureSts.ret;
}

void stubs_set_ASREngineControlActive_ASREngineControlActive(PassiveActive2_T par)
{
	p.Rte_ASREngineControlActive_ASREngineControlActive.par = par;
}

void stubs_set_EngineSpeed_EngineSpeed(SpeedRpm16bit_T par)
{
	p.Rte_EngineSpeed_EngineSpeed.par = par;
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

void stubs_set_TransmissionShiftInProcess_TransmissionShiftInProcess(TransmissionShiftInProcess_T par)
{
	p.Rte_TransmissionShiftInProcess_TransmissionShiftInProcess.par = par;
}

void stubs_set_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged(DisengageEngage_T par)
{
	p.Rte_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged.par = par;
}

void stubs_set_TransmissionCurrentGear_TransmissionCurrentGear(TransmissionGear_T par)
{
	p.Rte_TransmissionCurrentGear_TransmissionCurrentGear.par = par;
}

void stubs_set_ACC_SGO_Status_ACC_SGO_Status(ACC_SGO_Status_T par)
{
	p.Rte_ACC_SGO_Status_ACC_SGO_Status.par = par;
}

void stubs_set_RoadInclinationPerc_RoadInclinationPerc(RoadInclinationPerc_T par)
{
	p.Rte_RoadInclinationPerc_RoadInclinationPerc.par = par;
}

void stubs_set_ABSAxle1Active_ABSAxle1Active(OffOn_T par)
{
	p.Rte_ABSAxle1Active_ABSAxle1Active.par = par;
}

void stubs_set_ABSAxle2Active_ABSAxle2Active(OffOn_T par)
{
	p.Rte_ABSAxle2Active_ABSAxle2Active.par = par;
}

void stubs_set_ABSAxle3Active_ABSAxle3Active(OffOn_T par)
{
	p.Rte_ABSAxle3Active_ABSAxle3Active.par = par;
}

void stubs_set_ABSAxle4Active_ABSAxle4Active(OffOn_T par)
{
	p.Rte_ABSAxle4Active_ABSAxle4Active.par = par;
}

void stubs_set_ABSAxle5Active_ABSAxle5Active(OffOn_T par)
{
	p.Rte_ABSAxle5Active_ABSAxle5Active.par = par;
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

void stubs_set_FASFullyOperational_FASFullyOperational(FASFullyOperational_T par)
{
	p.Rte_FASFullyOperational_FASFullyOperational.par = par;
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

void stubs_set_FrontRoadWheelAngleEstimate_FrontRoadWheelAngleEstimate(RoadWheelAngle_T par)
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

void stubs_set_PusherAxleLeftWheelSpeed_PusherAxleLeftWheelSpeed(Speed16bit_T par)
{
	p.Rte_PusherAxleLeftWheelSpeed_PusherAxleLeftWheelSpeed.par = par;
}

void stubs_set_PusherAxleLoad_AxleLoad(AxleLoad_T par)
{
	p.Rte_PusherAxleLoad_AxleLoad.par = par;
}

void stubs_set_PusherAxleRightWheelSpeed_PusherAxleRightWheelSpeed(Speed16bit_T par)
{
	p.Rte_PusherAxleRightWheelSpeed_PusherAxleRightWheelSpeed.par = par;
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

void stubs_set_ScndFrAxleLeftWheelSpeed_ScndFrAxleLeftWheelSpeed(Speed16bit_T par)
{
	p.Rte_ScndFrAxleLeftWheelSpeed_ScndFrAxleLeftWheelSpeed.par = par;
}

void stubs_set_ScndFrAxleRightWheelSpeed_ScndFrAxleRightWheelSpeed(Speed16bit_T par)
{
	p.Rte_ScndFrAxleRightWheelSpeed_ScndFrAxleRightWheelSpeed.par = par;
}

void stubs_set_SecondaryDriveAxleLoad_AxleLoad(AxleLoad_T par)
{
	p.Rte_SecondaryDriveAxleLoad_AxleLoad.par = par;
}

void stubs_set_SteeringWheelAngle_SteeringWheelAngle(SteeringWheelAngle_T par)
{
	p.Rte_SteeringWheelAngle_SteeringWheelAngle.par = par;
}

void stubs_set_TagAxleLeftWheelSpeed_TagAxleLeftWheelSpeed(Speed16bit_T par)
{
	p.Rte_TagAxleLeftWheelSpeed_TagAxleLeftWheelSpeed.par = par;
}

void stubs_set_TagAxleLoad_AxleLoad(AxleLoad_T par)
{
	p.Rte_TagAxleLoad_AxleLoad.par = par;
}

void stubs_set_TagAxleRightWheelSpeed_TagAxleRightWheelSpeed(Speed16bit_T par)
{
	p.Rte_TagAxleRightWheelSpeed_TagAxleRightWheelSpeed.par = par;
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

void stubs_set_ScndRrDriveAxleLeftWheelSpeed_ScndRrDriveAxleLeftWheelSpeed(Speed16bit_T par)
{
	p.Rte_ScndRrDriveAxleLeftWheelSpeed_ScndRrDriveAxleLeftWheelSpeed.par = par;
}

void stubs_set_ScndRrDriveAxleRightWheelSpeed_ScndRrDriveAxleRightWheelSpeed(Speed16bit_T par)
{
	p.Rte_ScndRrDriveAxleRightWheelSpeed_ScndRrDriveAxleRightWheelSpeed.par = par;
}

void stubs_set_FrontAxleSpeed_FrontAxleSpeed(Speed16bit_T par)
{
	p.Rte_FrontAxleSpeed_FrontAxleSpeed.par = par;
}

void stubs_set_ABSFullyOperational_ABSFullyOperational(FullyOperational_T par)
{
	p.Rte_ABSFullyOperational_ABSFullyOperational.par = par;
}

void _stubs_check_VehicleYawInertia_VehicleYawInertia(InertiaQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_VehicleYawInertia_VehicleYawInertia.par.Inertia != expected->Inertia)
	{
		printf("%s in %s on line: %d, Inertia: expected %d but was %d\n", file, function, line, expected->Inertia, p.Rte_VehicleYawInertia_VehicleYawInertia.par.Inertia);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_VehicleYawInertia_VehicleYawInertia.par.Inertia == expected->Inertia);
	if (p.Rte_VehicleYawInertia_VehicleYawInertia.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_VehicleYawInertia_VehicleYawInertia.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_VehicleYawInertia_VehicleYawInertia.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_VehicleRollInertia_VehicleRollInertia(InertiaQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_VehicleRollInertia_VehicleRollInertia.par.Inertia != expected->Inertia)
	{
		printf("%s in %s on line: %d, Inertia: expected %d but was %d\n", file, function, line, expected->Inertia, p.Rte_VehicleRollInertia_VehicleRollInertia.par.Inertia);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_VehicleRollInertia_VehicleRollInertia.par.Inertia == expected->Inertia);
	if (p.Rte_VehicleRollInertia_VehicleRollInertia.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_VehicleRollInertia_VehicleRollInertia.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_VehicleRollInertia_VehicleRollInertia.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_VehiclePitchInertia_VehiclePitchInertia(InertiaQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_VehiclePitchInertia_VehiclePitchInertia.par.Inertia != expected->Inertia)
	{
		printf("%s in %s on line: %d, Inertia: expected %d but was %d\n", file, function, line, expected->Inertia, p.Rte_VehiclePitchInertia_VehiclePitchInertia.par.Inertia);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_VehiclePitchInertia_VehiclePitchInertia.par.Inertia == expected->Inertia);
	if (p.Rte_VehiclePitchInertia_VehiclePitchInertia.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_VehiclePitchInertia_VehiclePitchInertia.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_VehiclePitchInertia_VehiclePitchInertia.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_RearAxleCurvature_RearAxleCurvature(AxleCurvature_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_RearAxleCurvature_RearAxleCurvature.par.Curvature != expected->Curvature)
	{
		printf("%s in %s on line: %d, Curvature: expected %d but was %d\n", file, function, line, expected->Curvature, p.Rte_RearAxleCurvature_RearAxleCurvature.par.Curvature);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_RearAxleCurvature_RearAxleCurvature.par.Curvature == expected->Curvature);
	if (p.Rte_RearAxleCurvature_RearAxleCurvature.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_RearAxleCurvature_RearAxleCurvature.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_RearAxleCurvature_RearAxleCurvature.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_SpeedOverGround_SpeedOverGround(SpeedQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_SpeedOverGround_SpeedOverGround.par.Speed != expected->Speed)
	{
		printf("%s in %s on line: %d, Speed: expected %d but was %d\n", file, function, line, expected->Speed, p.Rte_SpeedOverGround_SpeedOverGround.par.Speed);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_SpeedOverGround_SpeedOverGround.par.Speed == expected->Speed);
	if (p.Rte_SpeedOverGround_SpeedOverGround.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_SpeedOverGround_SpeedOverGround.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_SpeedOverGround_SpeedOverGround.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_LongitudinalAccelerationQ_LongitudinalAccelerationQ(AccelerationQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_LongitudinalAccelerationQ_LongitudinalAccelerationQ.par.Acceleration != expected->Acceleration)
	{
		printf("%s in %s on line: %d, Acceleration: expected %d but was %d\n", file, function, line, expected->Acceleration, p.Rte_LongitudinalAccelerationQ_LongitudinalAccelerationQ.par.Acceleration);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_LongitudinalAccelerationQ_LongitudinalAccelerationQ.par.Acceleration == expected->Acceleration);
	if (p.Rte_LongitudinalAccelerationQ_LongitudinalAccelerationQ.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_LongitudinalAccelerationQ_LongitudinalAccelerationQ.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_LongitudinalAccelerationQ_LongitudinalAccelerationQ.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_ArticulationAngle_ArticulationAngle(AngleQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_ArticulationAngle_ArticulationAngle.par.Angle != expected->Angle)
	{
		printf("%s in %s on line: %d, Angle: expected %d but was %d\n", file, function, line, expected->Angle, p.Rte_ArticulationAngle_ArticulationAngle.par.Angle);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_ArticulationAngle_ArticulationAngle.par.Angle == expected->Angle);
	if (p.Rte_ArticulationAngle_ArticulationAngle.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_ArticulationAngle_ArticulationAngle.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_ArticulationAngle_ArticulationAngle.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_FrontAxleLoadQ_AxleLoadQ_I(LoadQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_FrontAxleLoadQ_AxleLoadQ_I.par.Load != expected->Load)
	{
		printf("%s in %s on line: %d, Load: expected %d but was %d\n", file, function, line, expected->Load, p.Rte_FrontAxleLoadQ_AxleLoadQ_I.par.Load);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_FrontAxleLoadQ_AxleLoadQ_I.par.Load == expected->Load);
	if (p.Rte_FrontAxleLoadQ_AxleLoadQ_I.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_FrontAxleLoadQ_AxleLoadQ_I.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_FrontAxleLoadQ_AxleLoadQ_I.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_PusherAxleLoadQ_AxleLoadQ_I(LoadQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_PusherAxleLoadQ_AxleLoadQ_I.par.Load != expected->Load)
	{
		printf("%s in %s on line: %d, Load: expected %d but was %d\n", file, function, line, expected->Load, p.Rte_PusherAxleLoadQ_AxleLoadQ_I.par.Load);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_PusherAxleLoadQ_AxleLoadQ_I.par.Load == expected->Load);
	if (p.Rte_PusherAxleLoadQ_AxleLoadQ_I.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_PusherAxleLoadQ_AxleLoadQ_I.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_PusherAxleLoadQ_AxleLoadQ_I.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_DriveAxleLoadQ_AxleLoadQ_I(LoadQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_DriveAxleLoadQ_AxleLoadQ_I.par.Load != expected->Load)
	{
		printf("%s in %s on line: %d, Load: expected %d but was %d\n", file, function, line, expected->Load, p.Rte_DriveAxleLoadQ_AxleLoadQ_I.par.Load);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_DriveAxleLoadQ_AxleLoadQ_I.par.Load == expected->Load);
	if (p.Rte_DriveAxleLoadQ_AxleLoadQ_I.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_DriveAxleLoadQ_AxleLoadQ_I.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_DriveAxleLoadQ_AxleLoadQ_I.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_TrailerAxleLoadQ_AxleLoadQ_I(LoadQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_TrailerAxleLoadQ_AxleLoadQ_I.par.Load != expected->Load)
	{
		printf("%s in %s on line: %d, Load: expected %d but was %d\n", file, function, line, expected->Load, p.Rte_TrailerAxleLoadQ_AxleLoadQ_I.par.Load);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_TrailerAxleLoadQ_AxleLoadQ_I.par.Load == expected->Load);
	if (p.Rte_TrailerAxleLoadQ_AxleLoadQ_I.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_TrailerAxleLoadQ_AxleLoadQ_I.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_TrailerAxleLoadQ_AxleLoadQ_I.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_RearAxleLifted_RearAxleLifted_I(LiftedQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_RearAxleLifted_RearAxleLifted_I.par.Lifted != expected->Lifted)
	{
		printf("%s in %s on line: %d, Lifted: expected %d but was %d\n", file, function, line, expected->Lifted, p.Rte_RearAxleLifted_RearAxleLifted_I.par.Lifted);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_RearAxleLifted_RearAxleLifted_I.par.Lifted == expected->Lifted);
	if (p.Rte_RearAxleLifted_RearAxleLifted_I.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_RearAxleLifted_RearAxleLifted_I.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_RearAxleLifted_RearAxleLifted_I.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_MotionState_MotionState_I(MotionStateQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_MotionState_MotionState_I.par.State != expected->State)
	{
		printf("%s in %s on line: %d, State: expected %d but was %d\n", file, function, line, expected->State, p.Rte_MotionState_MotionState_I.par.State);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_MotionState_MotionState_I.par.State == expected->State);
	if (p.Rte_MotionState_MotionState_I.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_MotionState_MotionState_I.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_MotionState_MotionState_I.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_TrailerConnected_TrailerConnected(TrailerConnectedQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_TrailerConnected_TrailerConnected.par.Connected != expected->Connected)
	{
		printf("%s in %s on line: %d, Connected: expected %d but was %d\n", file, function, line, expected->Connected, p.Rte_TrailerConnected_TrailerConnected.par.Connected);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_TrailerConnected_TrailerConnected.par.Connected == expected->Connected);
	if (p.Rte_TrailerConnected_TrailerConnected.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_TrailerConnected_TrailerConnected.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_TrailerConnected_TrailerConnected.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_VehicleStandstill_VehicleStandstill(StandstillQ_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_VehicleStandstill_VehicleStandstill.par.StandStill != expected->StandStill)
	{
		printf("%s in %s on line: %d, StandStill: expected %d but was %d\n", file, function, line, expected->StandStill, p.Rte_VehicleStandstill_VehicleStandstill.par.StandStill);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_VehicleStandstill_VehicleStandstill.par.StandStill == expected->StandStill);
	if (p.Rte_VehicleStandstill_VehicleStandstill.par.QualityFlag != expected->QualityFlag)
	{
		printf("%s in %s on line: %d, QualityFlag: expected %d but was %d\n", file, function, line, expected->QualityFlag, p.Rte_VehicleStandstill_VehicleStandstill.par.QualityFlag);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_VehicleStandstill_VehicleStandstill.par.QualityFlag == expected->QualityFlag);
}

void _stubs_check_VehicleStructureSts_VehicleStructureSts(VehicleStructureSts_T* expected, const char *file, const char *function, const int line)
{
	if (p.Rte_VehicleStructureSts_VehicleStructureSts.par.Mass_RE != expected->Mass_RE)
	{
		printf("%s in %s on line: %d, Mass_RE: expected %d but was %d\n", file, function, line, expected->Mass_RE, p.Rte_VehicleStructureSts_VehicleStructureSts.par.Mass_RE);
	}
	CU_ASSERT_TRUE_FATAL(p.Rte_VehicleStructureSts_VehicleStructureSts.par.Mass_RE == expected->Mass_RE);
}

