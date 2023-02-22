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
		SpeedRpm16bit_T par;
		Std_ReturnType ret;
	} Rte_EngineSpeed_EngineSpeed;

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
		TransmissionShiftInProcess_T par;
		Std_ReturnType ret;
	} Rte_TransmissionShiftInProcess_TransmissionShiftInProcess;

	struct
	{
		DisengageEngage_T par;
		Std_ReturnType ret;
	} Rte_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged;

	struct
	{
		TransmissionGear_T par;
		Std_ReturnType ret;
	} Rte_TransmissionCurrentGear_TransmissionCurrentGear;

	struct
	{
		ACC_SGO_Status_T par;
		Std_ReturnType ret;
	} Rte_ACC_SGO_Status_ACC_SGO_Status;

	struct
	{
		RoadInclinationPerc_T par;
		Std_ReturnType ret;
	} Rte_RoadInclinationPerc_RoadInclinationPerc;

	struct
	{
		OffOn_T par;
		Std_ReturnType ret;
	} Rte_ABSAxle1Active_ABSAxle1Active;

	struct
	{
		OffOn_T par;
		Std_ReturnType ret;
	} Rte_ABSAxle2Active_ABSAxle2Active;

	struct
	{
		OffOn_T par;
		Std_ReturnType ret;
	} Rte_ABSAxle3Active_ABSAxle3Active;

	struct
	{
		OffOn_T par;
		Std_ReturnType ret;
	} Rte_ABSAxle4Active_ABSAxle4Active;

	struct
	{
		OffOn_T par;
		Std_ReturnType ret;
	} Rte_ABSAxle5Active_ABSAxle5Active;

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
		FASFullyOperational_T par;
		Std_ReturnType ret;
	} Rte_FASFullyOperational_FASFullyOperational;

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
		RoadWheelAngle_T par;
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
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_PusherAxleLeftWheelSpeed_PusherAxleLeftWheelSpeed;

	struct
	{
		AxleLoad_T par;
		Std_ReturnType ret;
	} Rte_PusherAxleLoad_AxleLoad;

	struct
	{
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_PusherAxleRightWheelSpeed_PusherAxleRightWheelSpeed;

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
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_ScndFrAxleLeftWheelSpeed_ScndFrAxleLeftWheelSpeed;

	struct
	{
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_ScndFrAxleRightWheelSpeed_ScndFrAxleRightWheelSpeed;

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
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_TagAxleLeftWheelSpeed_TagAxleLeftWheelSpeed;

	struct
	{
		AxleLoad_T par;
		Std_ReturnType ret;
	} Rte_TagAxleLoad_AxleLoad;

	struct
	{
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_TagAxleRightWheelSpeed_TagAxleRightWheelSpeed;

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
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_ScndRrDriveAxleLeftWheelSpeed_ScndRrDriveAxleLeftWheelSpeed;

	struct
	{
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_ScndRrDriveAxleRightWheelSpeed_ScndRrDriveAxleRightWheelSpeed;

	struct
	{
		Speed16bit_T par;
		Std_ReturnType ret;
	} Rte_FrontAxleSpeed_FrontAxleSpeed;

	struct
	{
		FullyOperational_T par;
		Std_ReturnType ret;
	} Rte_ABSFullyOperational_ABSFullyOperational;

	struct
	{
		InertiaQ_T par;
		Std_ReturnType ret;
	} Rte_VehicleYawInertia_VehicleYawInertia;

	struct
	{
		InertiaQ_T par;
		Std_ReturnType ret;
	} Rte_VehicleRollInertia_VehicleRollInertia;

	struct
	{
		InertiaQ_T par;
		Std_ReturnType ret;
	} Rte_VehiclePitchInertia_VehiclePitchInertia;

	struct
	{
		AxleCurvature_T par;
		Std_ReturnType ret;
	} Rte_RearAxleCurvature_RearAxleCurvature;

	struct
	{
		SpeedQ_T par;
		Std_ReturnType ret;
	} Rte_SpeedOverGround_SpeedOverGround;

	struct
	{
		AccelerationQ_T par;
		Std_ReturnType ret;
	} Rte_LongitudinalAccelerationQ_LongitudinalAccelerationQ;

	struct
	{
		AngleQ_T par;
		Std_ReturnType ret;
	} Rte_ArticulationAngle_ArticulationAngle;

	struct
	{
		LoadQ_T par;
		Std_ReturnType ret;
	} Rte_FrontAxleLoadQ_AxleLoadQ_I;

	struct
	{
		LoadQ_T par;
		Std_ReturnType ret;
	} Rte_PusherAxleLoadQ_AxleLoadQ_I;

	struct
	{
		LoadQ_T par;
		Std_ReturnType ret;
	} Rte_DriveAxleLoadQ_AxleLoadQ_I;

	struct
	{
		LoadQ_T par;
		Std_ReturnType ret;
	} Rte_TrailerAxleLoadQ_AxleLoadQ_I;

	struct
	{
		LiftedQ_T par;
		Std_ReturnType ret;
	} Rte_RearAxleLifted_RearAxleLifted_I;

	struct
	{
		MotionStateQ_T par;
		Std_ReturnType ret;
	} Rte_MotionState_MotionState_I;

	struct
	{
		TrailerConnectedQ_T par;
		Std_ReturnType ret;
	} Rte_TrailerConnected_TrailerConnected;

	struct
	{
		StandstillQ_T par;
		Std_ReturnType ret;
	} Rte_VehicleStandstill_VehicleStandstill;

	struct
	{
		VehicleStructureSts_T par;
		Std_ReturnType ret;
	} Rte_VehicleStructureSts_VehicleStructureSts;

} StubSignals_Type;

extern StubSignals_Type p;

void stubs_set_ASREngineControlActive_ASREngineControlActive(PassiveActive2_T par);
void stubs_set_EngineSpeed_EngineSpeed(SpeedRpm16bit_T par);
void stubs_set_ActualEnginePercentTorque_ActualEnginePercentTorque(Percent8bit125NegOffset_T par);
void stubs_set_ActualDrvlnRetdrPercentTorque_ActualDrvlnRetdrPercentTorque(Percent8bit125NegOffset_T par);
void stubs_set_EngineReferenceTorque_EngineReferenceTorque(Torque16bit_T par);
void stubs_set_TransmissionActualGearRatio_TransmissionActualGearRatio(TransmissionActualGearRatio_T par);
void stubs_set_TransmissionShiftInProcess_TransmissionShiftInProcess(TransmissionShiftInProcess_T par);
void stubs_set_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged(DisengageEngage_T par);
void stubs_set_TransmissionCurrentGear_TransmissionCurrentGear(TransmissionGear_T par);
void stubs_set_ACC_SGO_Status_ACC_SGO_Status(ACC_SGO_Status_T par);
void stubs_set_RoadInclinationPerc_RoadInclinationPerc(RoadInclinationPerc_T par);
void stubs_set_ABSAxle1Active_ABSAxle1Active(OffOn_T par);
void stubs_set_ABSAxle2Active_ABSAxle2Active(OffOn_T par);
void stubs_set_ABSAxle3Active_ABSAxle3Active(OffOn_T par);
void stubs_set_ABSAxle4Active_ABSAxle4Active(OffOn_T par);
void stubs_set_ABSAxle5Active_ABSAxle5Active(OffOn_T par);
void stubs_set_ASRBrakeControlActive_ASRBrakeControlActive(PassiveActive2_T par);
void stubs_set_ActualEHPusherWheelAngle_ActuaEHPusherWheelAngle(uint16 par);
void stubs_set_ActualEHTagWheelAngle_ActualEHTagWheelAngle(uint16 par);
void stubs_set_ActualTagWheelAngle_ActualTagWheelAngle(ActualTagWheelAngle_T par);
void stubs_set_DriveAxleLoad_AxleLoad(AxleLoad_T par);
void stubs_set_FASFullyOperational_FASFullyOperational(FASFullyOperational_T par);
void stubs_set_FrAxleLtWhlBrakeApplPrsHiRng_FrAxleLtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_FrAxleRtWhlBrakeApplPrsHiRng_FrAxleRtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_FrontAxle1Load_AxleLoad(AxleLoad_T par);
void stubs_set_FrontAxle2Load_AxleLoad(AxleLoad_T par);
void stubs_set_FrontAxleLeftWheelSpeed_FrontAxleLeftWheelSpeed(Speed16bit_T par);
void stubs_set_FrontAxleRightWheelSpeed_FrontAxleRightWheelSpeed(Speed16bit_T par);
void stubs_set_FrontRoadWheelAngleEstimate_FrontRoadWheelAngleEstimate(RoadWheelAngle_T par);
void stubs_set_KFactor_KFactor(KFactor_T par);
void stubs_set_LiftAxle1PositionStatus_LiftAxle1PositionStatus(LiftAxlePositionStatus_T par);
void stubs_set_LiftAxle2PositionStatus_LiftAxle2PositionStatus(LiftAxlePositionStatus_T par);
void stubs_set_LongitudinalAcceleration_LongitudinalAcceleration(Acceleration16bit_T par);
void stubs_set_PusherAxleLeftWheelSpeed_PusherAxleLeftWheelSpeed(Speed16bit_T par);
void stubs_set_PusherAxleLoad_AxleLoad(AxleLoad_T par);
void stubs_set_PusherAxleRightWheelSpeed_PusherAxleRightWheelSpeed(Speed16bit_T par);
void stubs_set_RearAxleLeftWheelSpeed_RearAxleLeftWheelSpeed(Speed16bit_T par);
void stubs_set_RearAxleRightWheelSpeed_RearAxleRightWheelSpeed(Speed16bit_T par);
void stubs_set_RearAxleSteeringFunctionStatus_RearAxleSteeringFunctionStatus(RearAxleSteeringFunctionStatus_T par);
void stubs_set_RrAxle1LtWhlBrakeApplPrsHiRng_RrAxle1LtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_RrAxle1RtWhlBrakeApplPrsHiRng_RrAxle1RtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_RrAxle2LtWhlBrakeApplPrsHiRng_RrAxle2LtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_RrAxle2RtWhlBrakeApplPrsHiRng_RrAxle2RtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_RrAxle3LtWhlBrakeApplPrsHiRng_RrAxle3LtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_RrAxle3RtWhlBrakeApplPrsHiRng_RrAxle3RtWhlBrakeApplPrsHiRng(PressureFactor5_T par);
void stubs_set_ScndFrAxleLeftWheelSpeed_ScndFrAxleLeftWheelSpeed(Speed16bit_T par);
void stubs_set_ScndFrAxleRightWheelSpeed_ScndFrAxleRightWheelSpeed(Speed16bit_T par);
void stubs_set_SecondaryDriveAxleLoad_AxleLoad(AxleLoad_T par);
void stubs_set_SteeringWheelAngle_SteeringWheelAngle(SteeringWheelAngle_T par);
void stubs_set_TagAxleLeftWheelSpeed_TagAxleLeftWheelSpeed(Speed16bit_T par);
void stubs_set_TagAxleLoad_AxleLoad(AxleLoad_T par);
void stubs_set_TagAxleRightWheelSpeed_TagAxleRightWheelSpeed(Speed16bit_T par);
void stubs_set_TransmOutputShaftSpeedSigned_TransmOutputShaftSpeedSigned(SpeedRpm16bitMinus4000_T par);
void stubs_set_XPRsystemstate_XPRsystemstate(XPRsystemstate_T par);
void stubs_set_YawRate_YawRate(uint16 par);
void stubs_set_VehicleMode_VehicleMode(VehicleMode_T par);
void stubs_set_ScndRrDriveAxleLeftWheelSpeed_ScndRrDriveAxleLeftWheelSpeed(Speed16bit_T par);
void stubs_set_ScndRrDriveAxleRightWheelSpeed_ScndRrDriveAxleRightWheelSpeed(Speed16bit_T par);
void stubs_set_FrontAxleSpeed_FrontAxleSpeed(Speed16bit_T par);
void stubs_set_ABSFullyOperational_ABSFullyOperational(FullyOperational_T par);
#define stubs_check_VehicleYawInertia_VehicleYawInertia(expected) _stubs_check_VehicleYawInertia_VehicleYawInertia(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_VehicleYawInertia_VehicleYawInertia(InertiaQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_VehicleRollInertia_VehicleRollInertia(expected) _stubs_check_VehicleRollInertia_VehicleRollInertia(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_VehicleRollInertia_VehicleRollInertia(InertiaQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_VehiclePitchInertia_VehiclePitchInertia(expected) _stubs_check_VehiclePitchInertia_VehiclePitchInertia(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_VehiclePitchInertia_VehiclePitchInertia(InertiaQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_RearAxleCurvature_RearAxleCurvature(expected) _stubs_check_RearAxleCurvature_RearAxleCurvature(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_RearAxleCurvature_RearAxleCurvature(AxleCurvature_T* expected, const char *file, const char *function, const int line);

#define stubs_check_SpeedOverGround_SpeedOverGround(expected) _stubs_check_SpeedOverGround_SpeedOverGround(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_SpeedOverGround_SpeedOverGround(SpeedQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_LongitudinalAccelerationQ_LongitudinalAccelerationQ(expected) _stubs_check_LongitudinalAccelerationQ_LongitudinalAccelerationQ(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_LongitudinalAccelerationQ_LongitudinalAccelerationQ(AccelerationQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_ArticulationAngle_ArticulationAngle(expected) _stubs_check_ArticulationAngle_ArticulationAngle(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_ArticulationAngle_ArticulationAngle(AngleQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_FrontAxleLoadQ_AxleLoadQ_I(expected) _stubs_check_FrontAxleLoadQ_AxleLoadQ_I(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_FrontAxleLoadQ_AxleLoadQ_I(LoadQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_PusherAxleLoadQ_AxleLoadQ_I(expected) _stubs_check_PusherAxleLoadQ_AxleLoadQ_I(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_PusherAxleLoadQ_AxleLoadQ_I(LoadQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_DriveAxleLoadQ_AxleLoadQ_I(expected) _stubs_check_DriveAxleLoadQ_AxleLoadQ_I(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_DriveAxleLoadQ_AxleLoadQ_I(LoadQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_TrailerAxleLoadQ_AxleLoadQ_I(expected) _stubs_check_TrailerAxleLoadQ_AxleLoadQ_I(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_TrailerAxleLoadQ_AxleLoadQ_I(LoadQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_RearAxleLifted_RearAxleLifted_I(expected) _stubs_check_RearAxleLifted_RearAxleLifted_I(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_RearAxleLifted_RearAxleLifted_I(LiftedQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_MotionState_MotionState_I(expected) _stubs_check_MotionState_MotionState_I(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_MotionState_MotionState_I(MotionStateQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_TrailerConnected_TrailerConnected(expected) _stubs_check_TrailerConnected_TrailerConnected(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_TrailerConnected_TrailerConnected(TrailerConnectedQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_VehicleStandstill_VehicleStandstill(expected) _stubs_check_VehicleStandstill_VehicleStandstill(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_VehicleStandstill_VehicleStandstill(StandstillQ_T* expected, const char *file, const char *function, const int line);

#define stubs_check_VehicleStructureSts_VehicleStructureSts(expected) _stubs_check_VehicleStructureSts_VehicleStructureSts(expected, __FILE__, __FUNCTION__, __LINE__);
void _stubs_check_VehicleStructureSts_VehicleStructureSts(VehicleStructureSts_T* expected, const char *file, const char *function, const int line);

#endif
