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
 * @file  Se_rteData.h
 * @brief 
 *
 ****************************************************************************/
#ifndef __C_SE_RTEDATA_H__
#define __C_SE_RTEDATA_H__
#include "Rte_StateEstimation.h"

void Se_rteData(void)
{
	{PassiveActive2_T aSREngineControlActive;
	(void)Rte_Read_ASREngineControlActive_ASREngineControlActive(&aSREngineControlActive);
	/*dummy*/ rx->aSREngineControlActive = aSREngineControlActive;}

	{SpeedRpm16bit_T engineSpeed;
	(void)Rte_Read_EngineSpeed_EngineSpeed(&engineSpeed);
	/*dummy*/ rx->engineSpeed = engineSpeed;}

	{Percent8bit125NegOffset_T actualEnginePercentTorque;
	(void)Rte_Read_ActualEnginePercentTorque_ActualEnginePercentTorque(&actualEnginePercentTorque);
	/*dummy*/ rx->actualEnginePercentTorque = actualEnginePercentTorque;}

	{Percent8bit125NegOffset_T actualDrvlnRetdrPercentTorque;
	(void)Rte_Read_ActualDrvlnRetdrPercentTorque_ActualDrvlnRetdrPercentTorque(&actualDrvlnRetdrPercentTorque);
	/*dummy*/ rx->actualDrvlnRetdrPercentTorque = actualDrvlnRetdrPercentTorque;}

	{Torque16bit_T engineReferenceTorque;
	(void)Rte_Read_EngineReferenceTorque_EngineReferenceTorque(&engineReferenceTorque);
	/*dummy*/ rx->engineReferenceTorque = engineReferenceTorque;}

	{TransmissionActualGearRatio_T transmissionActualGearRatio;
	(void)Rte_Read_TransmissionActualGearRatio_TransmissionActualGearRatio(&transmissionActualGearRatio);
	/*dummy*/ rx->transmissionActualGearRatio = transmissionActualGearRatio;}

	{TransmissionShiftInProcess_T transmissionShiftInProcess;
	(void)Rte_Read_TransmissionShiftInProcess_TransmissionShiftInProcess(&transmissionShiftInProcess);
	/*dummy*/ rx->transmissionShiftInProcess = transmissionShiftInProcess;}

	{DisengageEngage_T transmissionDrivelineEngaged;
	(void)Rte_Read_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged(&transmissionDrivelineEngaged);
	/*dummy*/ rx->transmissionDrivelineEngaged = transmissionDrivelineEngaged;}

	{TransmissionGear_T transmissionCurrentGear;
	(void)Rte_Read_TransmissionCurrentGear_TransmissionCurrentGear(&transmissionCurrentGear);
	/*dummy*/ rx->transmissionCurrentGear = transmissionCurrentGear;}

	{ACC_SGO_Status_T aCC_SGO_Status;
	(void)Rte_Read_ACC_SGO_Status_ACC_SGO_Status(&aCC_SGO_Status);
	/*dummy*/ rx->aCC_SGO_Status = aCC_SGO_Status;}

	{RoadInclinationPerc_T roadInclinationPerc;
	(void)Rte_Read_RoadInclinationPerc_RoadInclinationPerc(&roadInclinationPerc);
	/*dummy*/ rx->roadInclinationPerc = roadInclinationPerc;}

	{OffOn_T aBSAxle1Active;
	(void)Rte_Read_ABSAxle1Active_ABSAxle1Active(&aBSAxle1Active);
	/*dummy*/ rx->aBSAxle1Active = aBSAxle1Active;}

	{OffOn_T aBSAxle2Active;
	(void)Rte_Read_ABSAxle2Active_ABSAxle2Active(&aBSAxle2Active);
	/*dummy*/ rx->aBSAxle2Active = aBSAxle2Active;}

	{OffOn_T aBSAxle3Active;
	(void)Rte_Read_ABSAxle3Active_ABSAxle3Active(&aBSAxle3Active);
	/*dummy*/ rx->aBSAxle3Active = aBSAxle3Active;}

	{OffOn_T aBSAxle4Active;
	(void)Rte_Read_ABSAxle4Active_ABSAxle4Active(&aBSAxle4Active);
	/*dummy*/ rx->aBSAxle4Active = aBSAxle4Active;}

	{OffOn_T aBSAxle5Active;
	(void)Rte_Read_ABSAxle5Active_ABSAxle5Active(&aBSAxle5Active);
	/*dummy*/ rx->aBSAxle5Active = aBSAxle5Active;}

	{PassiveActive2_T aSRBrakeControlActive;
	(void)Rte_Read_ASRBrakeControlActive_ASRBrakeControlActive(&aSRBrakeControlActive);
	/*dummy*/ rx->aSRBrakeControlActive = aSRBrakeControlActive;}

	{uint16 actuaEHPusherWheelAngle;
	(void)Rte_Read_ActualEHPusherWheelAngle_ActuaEHPusherWheelAngle(&actuaEHPusherWheelAngle);
	/*dummy*/ rx->actuaEHPusherWheelAngle = actuaEHPusherWheelAngle;}

	{uint16 actualEHTagWheelAngle;
	(void)Rte_Read_ActualEHTagWheelAngle_ActualEHTagWheelAngle(&actualEHTagWheelAngle);
	/*dummy*/ rx->actualEHTagWheelAngle = actualEHTagWheelAngle;}

	{ActualTagWheelAngle_T actualTagWheelAngle;
	(void)Rte_Read_ActualTagWheelAngle_ActualTagWheelAngle(&actualTagWheelAngle);
	/*dummy*/ rx->actualTagWheelAngle = actualTagWheelAngle;}

	{AxleLoad_T axleLoad;
	(void)Rte_Read_DriveAxleLoad_AxleLoad(&axleLoad);
	/*dummy*/ rx->axleLoad = axleLoad;}

	{FASFullyOperational_T fASFullyOperational;
	(void)Rte_Read_FASFullyOperational_FASFullyOperational(&fASFullyOperational);
	/*dummy*/ rx->fASFullyOperational = fASFullyOperational;}

	{PressureFactor5_T frAxleLtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_FrAxleLtWhlBrakeApplPrsHiRng_FrAxleLtWhlBrakeApplPrsHiRng(&frAxleLtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->frAxleLtWhlBrakeApplPrsHiRng = frAxleLtWhlBrakeApplPrsHiRng;}

	{PressureFactor5_T frAxleRtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_FrAxleRtWhlBrakeApplPrsHiRng_FrAxleRtWhlBrakeApplPrsHiRng(&frAxleRtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->frAxleRtWhlBrakeApplPrsHiRng = frAxleRtWhlBrakeApplPrsHiRng;}

	{AxleLoad_T axleLoad;
	(void)Rte_Read_FrontAxle1Load_AxleLoad(&axleLoad);
	/*dummy*/ rx->axleLoad = axleLoad;}

	{AxleLoad_T axleLoad;
	(void)Rte_Read_FrontAxle2Load_AxleLoad(&axleLoad);
	/*dummy*/ rx->axleLoad = axleLoad;}

	{Speed16bit_T frontAxleLeftWheelSpeed;
	(void)Rte_Read_FrontAxleLeftWheelSpeed_FrontAxleLeftWheelSpeed(&frontAxleLeftWheelSpeed);
	/*dummy*/ rx->frontAxleLeftWheelSpeed = frontAxleLeftWheelSpeed;}

	{Speed16bit_T frontAxleRightWheelSpeed;
	(void)Rte_Read_FrontAxleRightWheelSpeed_FrontAxleRightWheelSpeed(&frontAxleRightWheelSpeed);
	/*dummy*/ rx->frontAxleRightWheelSpeed = frontAxleRightWheelSpeed;}

	{RoadWheelAngle_T frontRoadWheelAngleEstimate;
	(void)Rte_Read_FrontRoadWheelAngleEstimate_FrontRoadWheelAngleEstimate(&frontRoadWheelAngleEstimate);
	/*dummy*/ rx->frontRoadWheelAngleEstimate = frontRoadWheelAngleEstimate;}

	{KFactor_T kFactor;
	(void)Rte_Read_KFactor_KFactor(&kFactor);
	/*dummy*/ rx->kFactor = kFactor;}

	{LiftAxlePositionStatus_T liftAxle1PositionStatus;
	(void)Rte_Read_LiftAxle1PositionStatus_LiftAxle1PositionStatus(&liftAxle1PositionStatus);
	/*dummy*/ rx->liftAxle1PositionStatus = liftAxle1PositionStatus;}

	{LiftAxlePositionStatus_T liftAxle2PositionStatus;
	(void)Rte_Read_LiftAxle2PositionStatus_LiftAxle2PositionStatus(&liftAxle2PositionStatus);
	/*dummy*/ rx->liftAxle2PositionStatus = liftAxle2PositionStatus;}

	{Acceleration16bit_T longitudinalAcceleration;
	(void)Rte_Read_LongitudinalAcceleration_LongitudinalAcceleration(&longitudinalAcceleration);
	/*dummy*/ rx->longitudinalAcceleration = longitudinalAcceleration;}

	{Speed16bit_T pusherAxleLeftWheelSpeed;
	(void)Rte_Read_PusherAxleLeftWheelSpeed_PusherAxleLeftWheelSpeed(&pusherAxleLeftWheelSpeed);
	/*dummy*/ rx->pusherAxleLeftWheelSpeed = pusherAxleLeftWheelSpeed;}

	{AxleLoad_T axleLoad;
	(void)Rte_Read_PusherAxleLoad_AxleLoad(&axleLoad);
	/*dummy*/ rx->axleLoad = axleLoad;}

	{Speed16bit_T pusherAxleRightWheelSpeed;
	(void)Rte_Read_PusherAxleRightWheelSpeed_PusherAxleRightWheelSpeed(&pusherAxleRightWheelSpeed);
	/*dummy*/ rx->pusherAxleRightWheelSpeed = pusherAxleRightWheelSpeed;}

	{Speed16bit_T rearAxleLeftWheelSpeed;
	(void)Rte_Read_RearAxleLeftWheelSpeed_RearAxleLeftWheelSpeed(&rearAxleLeftWheelSpeed);
	/*dummy*/ rx->rearAxleLeftWheelSpeed = rearAxleLeftWheelSpeed;}

	{Speed16bit_T rearAxleRightWheelSpeed;
	(void)Rte_Read_RearAxleRightWheelSpeed_RearAxleRightWheelSpeed(&rearAxleRightWheelSpeed);
	/*dummy*/ rx->rearAxleRightWheelSpeed = rearAxleRightWheelSpeed;}

	{RearAxleSteeringFunctionStatus_T rearAxleSteeringFunctionStatus;
	(void)Rte_Read_RearAxleSteeringFunctionStatus_RearAxleSteeringFunctionStatus(&rearAxleSteeringFunctionStatus);
	/*dummy*/ rx->rearAxleSteeringFunctionStatus = rearAxleSteeringFunctionStatus;}

	{PressureFactor5_T rrAxle1LtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_RrAxle1LtWhlBrakeApplPrsHiRng_RrAxle1LtWhlBrakeApplPrsHiRng(&rrAxle1LtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->rrAxle1LtWhlBrakeApplPrsHiRng = rrAxle1LtWhlBrakeApplPrsHiRng;}

	{PressureFactor5_T rrAxle1RtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_RrAxle1RtWhlBrakeApplPrsHiRng_RrAxle1RtWhlBrakeApplPrsHiRng(&rrAxle1RtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->rrAxle1RtWhlBrakeApplPrsHiRng = rrAxle1RtWhlBrakeApplPrsHiRng;}

	{PressureFactor5_T rrAxle2LtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_RrAxle2LtWhlBrakeApplPrsHiRng_RrAxle2LtWhlBrakeApplPrsHiRng(&rrAxle2LtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->rrAxle2LtWhlBrakeApplPrsHiRng = rrAxle2LtWhlBrakeApplPrsHiRng;}

	{PressureFactor5_T rrAxle2RtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_RrAxle2RtWhlBrakeApplPrsHiRng_RrAxle2RtWhlBrakeApplPrsHiRng(&rrAxle2RtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->rrAxle2RtWhlBrakeApplPrsHiRng = rrAxle2RtWhlBrakeApplPrsHiRng;}

	{PressureFactor5_T rrAxle3LtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_RrAxle3LtWhlBrakeApplPrsHiRng_RrAxle3LtWhlBrakeApplPrsHiRng(&rrAxle3LtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->rrAxle3LtWhlBrakeApplPrsHiRng = rrAxle3LtWhlBrakeApplPrsHiRng;}

	{PressureFactor5_T rrAxle3RtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_RrAxle3RtWhlBrakeApplPrsHiRng_RrAxle3RtWhlBrakeApplPrsHiRng(&rrAxle3RtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->rrAxle3RtWhlBrakeApplPrsHiRng = rrAxle3RtWhlBrakeApplPrsHiRng;}

	{Speed16bit_T scndFrAxleLeftWheelSpeed;
	(void)Rte_Read_ScndFrAxleLeftWheelSpeed_ScndFrAxleLeftWheelSpeed(&scndFrAxleLeftWheelSpeed);
	/*dummy*/ rx->scndFrAxleLeftWheelSpeed = scndFrAxleLeftWheelSpeed;}

	{Speed16bit_T scndFrAxleRightWheelSpeed;
	(void)Rte_Read_ScndFrAxleRightWheelSpeed_ScndFrAxleRightWheelSpeed(&scndFrAxleRightWheelSpeed);
	/*dummy*/ rx->scndFrAxleRightWheelSpeed = scndFrAxleRightWheelSpeed;}

	{AxleLoad_T axleLoad;
	(void)Rte_Read_SecondaryDriveAxleLoad_AxleLoad(&axleLoad);
	/*dummy*/ rx->axleLoad = axleLoad;}

	{SteeringWheelAngle_T steeringWheelAngle;
	(void)Rte_Read_SteeringWheelAngle_SteeringWheelAngle(&steeringWheelAngle);
	/*dummy*/ rx->steeringWheelAngle = steeringWheelAngle;}

	{Speed16bit_T tagAxleLeftWheelSpeed;
	(void)Rte_Read_TagAxleLeftWheelSpeed_TagAxleLeftWheelSpeed(&tagAxleLeftWheelSpeed);
	/*dummy*/ rx->tagAxleLeftWheelSpeed = tagAxleLeftWheelSpeed;}

	{AxleLoad_T axleLoad;
	(void)Rte_Read_TagAxleLoad_AxleLoad(&axleLoad);
	/*dummy*/ rx->axleLoad = axleLoad;}

	{Speed16bit_T tagAxleRightWheelSpeed;
	(void)Rte_Read_TagAxleRightWheelSpeed_TagAxleRightWheelSpeed(&tagAxleRightWheelSpeed);
	/*dummy*/ rx->tagAxleRightWheelSpeed = tagAxleRightWheelSpeed;}

	{SpeedRpm16bitMinus4000_T transmOutputShaftSpeedSigned;
	(void)Rte_Read_TransmOutputShaftSpeedSigned_TransmOutputShaftSpeedSigned(&transmOutputShaftSpeedSigned);
	/*dummy*/ rx->transmOutputShaftSpeedSigned = transmOutputShaftSpeedSigned;}

	{XPRsystemstate_T xPRsystemstate;
	(void)Rte_Read_XPRsystemstate_XPRsystemstate(&xPRsystemstate);
	/*dummy*/ rx->xPRsystemstate = xPRsystemstate;}

	{uint16 yawRate;
	(void)Rte_Read_YawRate_YawRate(&yawRate);
	/*dummy*/ rx->yawRate = yawRate;}

	{VehicleMode_T vehicleMode;
	(void)Rte_Read_VehicleMode_VehicleMode(&vehicleMode);
	/*dummy*/ rx->vehicleMode = vehicleMode;}

	{Speed16bit_T scndRrDriveAxleLeftWheelSpeed;
	(void)Rte_Read_ScndRrDriveAxleLeftWheelSpeed_ScndRrDriveAxleLeftWheelSpeed(&scndRrDriveAxleLeftWheelSpeed);
	/*dummy*/ rx->scndRrDriveAxleLeftWheelSpeed = scndRrDriveAxleLeftWheelSpeed;}

	{Speed16bit_T scndRrDriveAxleRightWheelSpeed;
	(void)Rte_Read_ScndRrDriveAxleRightWheelSpeed_ScndRrDriveAxleRightWheelSpeed(&scndRrDriveAxleRightWheelSpeed);
	/*dummy*/ rx->scndRrDriveAxleRightWheelSpeed = scndRrDriveAxleRightWheelSpeed;}

	{Speed16bit_T frontAxleSpeed;
	(void)Rte_Read_FrontAxleSpeed_FrontAxleSpeed(&frontAxleSpeed);
	/*dummy*/ rx->frontAxleSpeed = frontAxleSpeed;}

	{FullyOperational_T aBSFullyOperational;
	(void)Rte_Read_ABSFullyOperational_ABSFullyOperational(&aBSFullyOperational);
	/*dummy*/ rx->aBSFullyOperational = aBSFullyOperational;}

	(void)Rte_Write_VehicleYawInertia_VehicleYawInertia((InertiaQ_T)(tx->data));

	(void)Rte_Write_VehicleRollInertia_VehicleRollInertia((InertiaQ_T)(tx->data));

	(void)Rte_Write_VehiclePitchInertia_VehiclePitchInertia((InertiaQ_T)(tx->data));

	(void)Rte_Write_RearAxleCurvature_RearAxleCurvature((AxleCurvature_T)(tx->data));

	(void)Rte_Write_SpeedOverGround_SpeedOverGround((SpeedQ_T)(tx->data));

	(void)Rte_Write_LongitudinalAccelerationQ_LongitudinalAccelerationQ((AccelerationQ_T)(tx->data));

	(void)Rte_Write_ArticulationAngle_ArticulationAngle((AngleQ_T)(tx->data));

	(void)Rte_Write_FrontAxleLoadQ_AxleLoadQ_I((LoadQ_T)(tx->data));

	(void)Rte_Write_PusherAxleLoadQ_AxleLoadQ_I((LoadQ_T)(tx->data));

	(void)Rte_Write_DriveAxleLoadQ_AxleLoadQ_I((LoadQ_T)(tx->data));

	(void)Rte_Write_TrailerAxleLoadQ_AxleLoadQ_I((LoadQ_T)(tx->data));

	(void)Rte_Write_RearAxleLifted_RearAxleLifted_I((LiftedQ_T)(tx->data));

	(void)Rte_Write_MotionState_MotionState_I((MotionStateQ_T)(tx->data));

	(void)Rte_Write_TrailerConnected_TrailerConnected((TrailerConnectedQ_T)(tx->data));

	(void)Rte_Write_VehicleStandstill_VehicleStandstill((StandstillQ_T)(tx->data));

	(void)Rte_Write_VehicleStructureSts_VehicleStructureSts((VehicleStructureSts_T)(tx->data));

};
#endif
