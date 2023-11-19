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
 * @file  rte_data.h
 * @brief 
 *
 ****************************************************************************/
#ifndef __C_RTE_DATA_H__
#define __C_RTE_DATA_H__
#include "Rte_StateEstimation.h"

void rte_data(void)
{
	{PassiveActive2_T aSREngineControlActive;
	(void)Rte_Read_ASREngineControlActive_ASREngineControlActive(&aSREngineControlActive);
	/*dummy*/ rx->aSREngineControlActive = aSREngineControlActive;}

	{Percent8bit125NegOffset_T actualEnginePercentTorque;
	(void)Rte_Read_ActualEnginePercentTorque_ActualEnginePercentTorque(&actualEnginePercentTorque);
	/*dummy*/ rx->actualEnginePercentTorque = actualEnginePercentTorque + (-125);}

	{Percent8bit125NegOffset_T actualDrvlnRetdrPercentTorque;
	(void)Rte_Read_ActualDrvlnRetdrPercentTorque_ActualDrvlnRetdrPercentTorque(&actualDrvlnRetdrPercentTorque);
	/*dummy*/ rx->actualDrvlnRetdrPercentTorque = actualDrvlnRetdrPercentTorque + (-125);}

	{Torque16bit_T engineReferenceTorque;
	(void)Rte_Read_EngineReferenceTorque_EngineReferenceTorque(&engineReferenceTorque);
	/*dummy*/ rx->engineReferenceTorque = engineReferenceTorque;}

	{TransmissionActualGearRatio_T transmissionActualGearRatio;
	(void)Rte_Read_TransmissionActualGearRatio_TransmissionActualGearRatio(&transmissionActualGearRatio);
	/*dummy*/ rx->transmissionActualGearRatio = 0.001*transmissionActualGearRatio;}

	{DisengageEngage_T transmissionDrivelineEngaged;
	(void)Rte_Read_TransmissionDrivelineEngaged_TransmissionDrivelineEngaged(&transmissionDrivelineEngaged);
	/*dummy*/ rx->transmissionDrivelineEngaged = transmissionDrivelineEngaged;}

	{RoadInclinationPerc_T roadInclinationPerc;
	(void)Rte_Read_RoadInclinationPerc_RoadInclinationPerc(&roadInclinationPerc);
	/*dummy*/ rx->roadInclinationPerc = roadInclinationPerc;}

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
	/*dummy*/ rx->actualTagWheelAngle = 0.01*actualTagWheelAngle + (-50);}

	{AxleLoad_T axleLoad;
	(void)Rte_Read_DriveAxleLoad_AxleLoad(&axleLoad);
	/*dummy*/ rx->axleLoad = axleLoad;}

	{PressureFactor5_T frAxleLtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_FrAxleLtWhlBrakeApplPrsHiRng_FrAxleLtWhlBrakeApplPrsHiRng(&frAxleLtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->frAxleLtWhlBrakeApplPrsHiRng = 5*frAxleLtWhlBrakeApplPrsHiRng;}

	{PressureFactor5_T frAxleRtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_FrAxleRtWhlBrakeApplPrsHiRng_FrAxleRtWhlBrakeApplPrsHiRng(&frAxleRtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->frAxleRtWhlBrakeApplPrsHiRng = 5*frAxleRtWhlBrakeApplPrsHiRng;}

	{AxleLoad_T axleLoad;
	(void)Rte_Read_FrontAxle1Load_AxleLoad(&axleLoad);
	/*dummy*/ rx->axleLoad = axleLoad;}

	{AxleLoad_T axleLoad;
	(void)Rte_Read_FrontAxle2Load_AxleLoad(&axleLoad);
	/*dummy*/ rx->axleLoad = axleLoad;}

	{Speed16bit_T frontAxleLeftWheelSpeed;
	(void)Rte_Read_FrontAxleLeftWheelSpeed_FrontAxleLeftWheelSpeed(&frontAxleLeftWheelSpeed);
	/*dummy*/ rx->frontAxleLeftWheelSpeed = 0.00390625*frontAxleLeftWheelSpeed;}

	{Speed16bit_T frontAxleRightWheelSpeed;
	(void)Rte_Read_FrontAxleRightWheelSpeed_FrontAxleRightWheelSpeed(&frontAxleRightWheelSpeed);
	/*dummy*/ rx->frontAxleRightWheelSpeed = 0.00390625*frontAxleRightWheelSpeed;}

	{RWhlAg_T frontRoadWheelAngleEstimate;
	(void)Rte_Read_FrontRoadWheelAngleEstimate_FrontRoadWheelAngleEstimate(&frontRoadWheelAngleEstimate);
	/*dummy*/ rx->frontRoadWheelAngleEstimate = 5E-005*frontRoadWheelAngleEstimate + (-1.6);}

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
	/*dummy*/ rx->longitudinalAcceleration = 0.00048828125*longitudinalAcceleration + (-15.687);}

	{AxleLoad_T axleLoad;
	(void)Rte_Read_PusherAxleLoad_AxleLoad(&axleLoad);
	/*dummy*/ rx->axleLoad = axleLoad;}

	{Speed16bit_T rearAxleLeftWheelSpeed;
	(void)Rte_Read_RearAxleLeftWheelSpeed_RearAxleLeftWheelSpeed(&rearAxleLeftWheelSpeed);
	/*dummy*/ rx->rearAxleLeftWheelSpeed = 0.00390625*rearAxleLeftWheelSpeed;}

	{Speed16bit_T rearAxleRightWheelSpeed;
	(void)Rte_Read_RearAxleRightWheelSpeed_RearAxleRightWheelSpeed(&rearAxleRightWheelSpeed);
	/*dummy*/ rx->rearAxleRightWheelSpeed = 0.00390625*rearAxleRightWheelSpeed;}

	{RearAxleSteeringFunctionStatus_T rearAxleSteeringFunctionStatus;
	(void)Rte_Read_RearAxleSteeringFunctionStatus_RearAxleSteeringFunctionStatus(&rearAxleSteeringFunctionStatus);
	/*dummy*/ rx->rearAxleSteeringFunctionStatus = rearAxleSteeringFunctionStatus;}

	{PressureFactor5_T rrAxle1LtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_RrAxle1LtWhlBrakeApplPrsHiRng_RrAxle1LtWhlBrakeApplPrsHiRng(&rrAxle1LtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->rrAxle1LtWhlBrakeApplPrsHiRng = 5*rrAxle1LtWhlBrakeApplPrsHiRng;}

	{PressureFactor5_T rrAxle1RtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_RrAxle1RtWhlBrakeApplPrsHiRng_RrAxle1RtWhlBrakeApplPrsHiRng(&rrAxle1RtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->rrAxle1RtWhlBrakeApplPrsHiRng = 5*rrAxle1RtWhlBrakeApplPrsHiRng;}

	{PressureFactor5_T rrAxle2LtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_RrAxle2LtWhlBrakeApplPrsHiRng_RrAxle2LtWhlBrakeApplPrsHiRng(&rrAxle2LtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->rrAxle2LtWhlBrakeApplPrsHiRng = 5*rrAxle2LtWhlBrakeApplPrsHiRng;}

	{PressureFactor5_T rrAxle2RtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_RrAxle2RtWhlBrakeApplPrsHiRng_RrAxle2RtWhlBrakeApplPrsHiRng(&rrAxle2RtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->rrAxle2RtWhlBrakeApplPrsHiRng = 5*rrAxle2RtWhlBrakeApplPrsHiRng;}

	{PressureFactor5_T rrAxle3LtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_RrAxle3LtWhlBrakeApplPrsHiRng_RrAxle3LtWhlBrakeApplPrsHiRng(&rrAxle3LtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->rrAxle3LtWhlBrakeApplPrsHiRng = 5*rrAxle3LtWhlBrakeApplPrsHiRng;}

	{PressureFactor5_T rrAxle3RtWhlBrakeApplPrsHiRng;
	(void)Rte_Read_RrAxle3RtWhlBrakeApplPrsHiRng_RrAxle3RtWhlBrakeApplPrsHiRng(&rrAxle3RtWhlBrakeApplPrsHiRng);
	/*dummy*/ rx->rrAxle3RtWhlBrakeApplPrsHiRng = 5*rrAxle3RtWhlBrakeApplPrsHiRng;}

	{AxleLoad_T axleLoad;
	(void)Rte_Read_SecondaryDriveAxleLoad_AxleLoad(&axleLoad);
	/*dummy*/ rx->axleLoad = axleLoad;}

	{SteeringWheelAngle_T steeringWheelAngle;
	(void)Rte_Read_SteeringWheelAngle_SteeringWheelAngle(&steeringWheelAngle);
	/*dummy*/ rx->steeringWheelAngle = 0.0009765625*steeringWheelAngle + (-31.374);}

	{AxleLoad_T axleLoad;
	(void)Rte_Read_TagAxleLoad_AxleLoad(&axleLoad);
	/*dummy*/ rx->axleLoad = axleLoad;}

	{SpeedRpm16bitMinus4000_T transmOutputShaftSpeedSigned;
	(void)Rte_Read_TransmOutputShaftSpeedSigned_TransmOutputShaftSpeedSigned(&transmOutputShaftSpeedSigned);
	/*dummy*/ rx->transmOutputShaftSpeedSigned = 0.125*transmOutputShaftSpeedSigned + (-4000);}

	{XPRsystemstate_T xPRsystemstate;
	(void)Rte_Read_XPRsystemstate_XPRsystemstate(&xPRsystemstate);
	/*dummy*/ rx->xPRsystemstate = xPRsystemstate;}

	{uint16 yawRate;
	(void)Rte_Read_YawRate_YawRate(&yawRate);
	/*dummy*/ rx->yawRate = 0.000122*yawRate + (-3.92);}

	{VehicleMode_T vehicleMode;
	(void)Rte_Read_VehicleMode_VehicleMode(&vehicleMode);
	/*dummy*/ rx->vehicleMode = vehicleMode;}

	{Percent8bit125NegOffset_T actualEngineRetarderPercentTrq;
	(void)Rte_Read_ActualEngineRetarderPercentTrq_ActualEngineRetarderPercentTrq(&actualEngineRetarderPercentTrq);
	/*dummy*/ rx->actualEngineRetarderPercentTrq = actualEngineRetarderPercentTrq + (-125);}

	(void)Rte_Write_AgrV_yawChassis_YawRateChassis((YawRateChassis_T)(tx->data));

	(void)Rte_Write_AgrA_yawChassis_YawAccChassis((YawAccChassis_T)(tx->data));

	(void)Rte_Write_V_spdXRefPoint_SpdXRefPoint((Speed_T)(tx->data));

	(void)Rte_Write_A_accXRefPoint_AccXRefPoint((Acceleration_T)(tx->data));

	(void)Rte_Write_A_accYRefPoint_AccYRefPoint((Acceleration_T)(tx->data));

	(void)Rte_Write_Ag_sideslipRefPoint_SideslipRefPoint((Angle_T)(tx->data));

	(void)Rte_Write_Crvt_pathRefPoint_CrvtPathRefPoint((Curvature_T)(tx->data));

	(void)Rte_Write_N_crvtFacRefPoint_CrvtFacRefPoint((CurvatureFac_T)(tx->data));

	(void)Rte_Write_L_equivalentRearAxlePosition_EquivalentRearAxlePos((EquivalentRearAxlePos_T)(tx->data));

	(void)Rte_Write_E_motionEstStatus_MotionEstStatus((MotionEstStatus_T)(tx->data));

	(void)Rte_Write_D_yawRateVari_YawRateVari((Variance_T)(tx->data));

	(void)Rte_Write_D_yawAccVari_YawAccVari((Variance_T)(tx->data));

	(void)Rte_Write_D_spdXVari_SpdXVari((Variance_T)(tx->data));

	(void)Rte_Write_D_spdYVari_SpdYVari((Variance_T)(tx->data));

	(void)Rte_Write_D_accXVari_AccXVari((Variance_T)(tx->data));

	(void)Rte_Write_D_accYVari_AccYVari((Variance_T)(tx->data));

	(void)Rte_Write_D_sideslipVari_SideslipVari((Variance_T)(tx->data));

	(void)Rte_Write_T_totalFilterLatencyEst_TotalFilterLatencyEst((Latency_T)(tx->data));

	(void)Rte_Write_Ag_chassisRollAngleEst_RollAngleChassisEst((Angle_T)(tx->data));

	(void)Rte_Write_E_chassisRollAngleEstQuality_RollAngleChassisEstQuality((RollAngleEstQly_T)(tx->data));

	(void)Rte_Write_A_spdXRateRefPoint_SpdXRateRefPoint((Acceleration_T)(tx->data));

	(void)Rte_Write_A_spdYRateRefPoint_SpdYRateRefPoint((Acceleration_T)(tx->data));

	(void)Rte_Write_Ag_roadWheelAngle_RoadWheelAngle((RoadWheelAngle_T2)(tx->data));

	(void)Rte_Write_A_accYDueToBankAngle_AccYDueToBankAngle((Acceleration_T)(tx->data));

	(void)Rte_Write_LongMotionDirection_LongMotionDirection((LongMotionDirection_sg_T)(tx->data));

	(void)Rte_Write_LongMotionDirectionQuality_LongMotionDirectionQuality((LongMotionDirectionQuality_T)(tx->data));

	(void)Rte_Write_LongMotionDirection_ErrorStatus_LongMotionDirection_ErrorStatus((LongMotionDirErrorSts_T)(tx->data));

	(void)Rte_Write_D_nonlinearSteeringRatio_NonlinearSteeringRatio((SteeringRatio_T)(tx->data));

	(void)Rte_Write_E_spdXRefPointQly_SpdXRefPointQly((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_spdYRefPointQly_SpdYRefPointQly((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_accXRefPointQly_AccXRefPointQly((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_accYRefPointQly_AccYRefPointQly((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_yawRateRearAxleQly_YawRateRearAxleQly((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_yawAccRearAxleQly_YawAccRearAxleQly((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_sideslipRefPointQly_SideslipRefPointQly((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_roadWheelAngleQly_RoadWheelAngleQly((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_crvtPathRefPointQly_CrvtPathRefPointQly((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_equivalentRearAxlePositionQly_EquivalentRearAxlePositionQly((SignalQuality_T)(tx->data));

	(void)Rte_Write_V_spdYRefPoint_SpdYRefPoint((Speed_T)(tx->data));

	(void)Rte_Write_V_spdAtWhl_Ax1L_V_spdAtWhl_Ax1L((V_spdAtWhl_Ax1L_T)(tx->data));

	(void)Rte_Write_V_spdAtWhl_Ax1R_V_spdAtWhl_Ax1R((V_spdAtWhl_Ax1R_T)(tx->data));

	(void)Rte_Write_V_spdAtWhl_Ax2L_V_spdAtWhl_Ax2L((V_spdAtWhl_Ax2L_T)(tx->data));

	(void)Rte_Write_V_spdAtWhl_Ax2R_V_spdAtWhl_Ax2R((V_spdAtWhl_Ax2R_T)(tx->data));

	(void)Rte_Write_V_spdAtWhl_Ax3L_V_spdAtWhl_Ax3L((V_spdAtWhl_Ax3L_T)(tx->data));

	(void)Rte_Write_V_spdAtWhl_Ax3R_V_spdAtWhl_Ax3R((V_spdAtWhl_Ax3R_T)(tx->data));

	(void)Rte_Write_V_spdAtWhl_Ax4L_V_spdAtWhl_Ax4L((V_spdAtWhl_Ax4L_T)(tx->data));

	(void)Rte_Write_V_spdAtWhl_Ax4R_V_spdAtWhl_Ax4R((V_spdAtWhl_Ax4R_T)(tx->data));

	(void)Rte_Write_V_spdAtWhl_Ax5L_V_spdAtWhl_Ax5L((V_spdAtWhl_Ax5L_T)(tx->data));

	(void)Rte_Write_V_spdAtWhl_Ax5R_V_spdAtWhl_Ax5R((V_spdAtWhl_Ax5R_T)(tx->data));

	(void)Rte_Write_E_spdAtWhlQly_Ax1L_E_spdAtWhlQly_Ax1L((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_spdAtWhlQly_Ax1R_E_spdAtWhlQly_Ax1R((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_spdAtWhlQly_Ax2L_E_spdAtWhlQly_Ax2L((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_spdAtWhlQly_Ax2R_E_spdAtWhlQly_Ax2R((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_spdAtWhlQly_Ax3L_E_spdAtWhlQly_Ax3L((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_spdAtWhlQly_Ax3R_E_spdAtWhlQly_Ax3R((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_spdAtWhlQly_Ax4L_E_spdAtWhlQly_Ax4L((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_spdAtWhlQly_Ax4R_E_spdAtWhlQly_Ax4R((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_spdAtWhlQly_Ax5R_E_spdAtWhlQly_Ax5R((SignalQuality_T)(tx->data));

	(void)Rte_Write_E_spdAtWhlQly_Ax5L_E_spdAtWhlQly_Ax5L((SignalQuality_T)(tx->data));

	P10VW_D_precLongAccMeas = Rte_Prm_P10VW_D_precLongAccMeas_v();
	P1AK9_SelfSteeredTagAxleThreshSpeed = Rte_Prm_P1AK9_SelfSteeredTagAxleThreshSpeed_v();
	X1C5B_D_lowSpdSnsrSelnLatAScaFac = Rte_Prm_X1C5B_D_lowSpdSnsrSelnLatAScaFac_v();
	X1C6U_D_FltHndlgIndirPrimSigFltScaFac = Rte_Prm_X1C6U_D_FltHndlgIndirPrimSigFltScaFac_v();
	P1A8I_ConfigAxle_4_axle_load_max = Rte_Prm_P1A8I_ConfigAxle_4_axle_load_max_v();
	P10VT_D_precYawJerkInput = Rte_Prm_P10VT_D_precYawJerkInput_v();
	P1A8A_ConfigAxle_4_p_thres = Rte_Prm_P1A8A_ConfigAxle_4_p_thres_v();
	X1C68_D_FltHndlgPrimSigFltScaFac = Rte_Prm_X1C68_D_FltHndlgPrimSigFltScaFac_v();
	P1A59_ConfigAxle_1_axle_type_liftable = Rte_Prm_P1A59_ConfigAxle_1_axle_type_liftable_v();
	P1A62_ConfigAxle_2_wh_rollingcircu = Rte_Prm_P1A62_ConfigAxle_2_wh_rollingcircu_v();
	P1A71_ConfigAxle_4_axle_type_steered = Rte_Prm_P1A71_ConfigAxle_4_axle_type_steered_v();
	X1C60_T_interventionNoTrustTime = Rte_Prm_X1C60_T_interventionNoTrustTime_v();
	P1BGV_SteeringRatio = Rte_Prm_P1BGV_SteeringRatio_v();
	P1L1L_VehicleType = Rte_Prm_P1L1L_VehicleType_v();
	P1A6U_ConfigAxle_2_axle_type_liftable = Rte_Prm_P1A6U_ConfigAxle_2_axle_type_liftable_v();
	P1A7N_ConfigAxle_3_wh_rollingcircu = Rte_Prm_P1A7N_ConfigAxle_3_wh_rollingcircu_v();
	X1C8Y_Tq_minEngineWheelTorque = Rte_Prm_X1C8Y_Tq_minEngineWheelTorque_v();
	X1C5E_D_lowSpdSnsrSelnWhlSpdScaFac = Rte_Prm_X1C5E_D_lowSpdSnsrSelnWhlSpdScaFac_v();
	P10WG_D_normSlipStfnAxle5 = Rte_Prm_P10WG_D_normSlipStfnAxle5_v();
	X1DCK_T_absAsrTurnOffDly = Rte_Prm_X1DCK_T_absAsrTurnOffDly_v();
	P10W2_M_Axle5SuspVertLoads[0] = (*Rte_Prm_P10W2_M_Axle5SuspVertLoads_v())[0];
	P10W2_M_Axle5SuspVertLoads[1] = (*Rte_Prm_P10W2_M_Axle5SuspVertLoads_v())[1];
	P1A7C_ConfigAxle_2_axle_load_max = Rte_Prm_P1A7C_ConfigAxle_2_axle_load_max_v();
	P10WU_M_Axle1SuspVertLoads[0] = (*Rte_Prm_P10WU_M_Axle1SuspVertLoads_v())[0];
	P10WU_M_Axle1SuspVertLoads[1] = (*Rte_Prm_P10WU_M_Axle1SuspVertLoads_v())[1];
	P1A8L_ConfigAxle_5_axle_type_liftable = Rte_Prm_P1A8L_ConfigAxle_5_axle_type_liftable_v();
	X1C48_Frq_lowSpdSnsrSelnTqFilFrq = Rte_Prm_X1C48_Frq_lowSpdSnsrSelnTqFilFrq_v();
	P1A6J_ConfigAxle_1_p_thres = Rte_Prm_P1A6J_ConfigAxle_1_p_thres_v();
	P1A6R_ConfigAxle_1_axle_load_max = Rte_Prm_P1A6R_ConfigAxle_1_axle_load_max_v();
	P10WD_D_normSlipStfnAxle2 = Rte_Prm_P10WD_D_normSlipStfnAxle2_v();
	P1A83_ConfigAxle_5_axle_load_max = Rte_Prm_P1A83_ConfigAxle_5_axle_load_max_v();
	P1KJ7_FAxleContactPatchOutside2OutsideDist = Rte_Prm_P1KJ7_FAxleContactPatchOutside2OutsideDist_v();
	P1CSG_RearAxleArrangement = Rte_Prm_P1CSG_RearAxleArrangement_v();
	P1A7Q_ConfigAxle_3_brake_factor = Rte_Prm_P1A7Q_ConfigAxle_3_brake_factor_v();
	X1DU3_T_absAsrRstDelayTime = Rte_Prm_X1DU3_T_absAsrRstDelayTime_v();
	P1B8U_VehicleTargetGeneratorSpeedLimits1 = Rte_Prm_P1B8U_VehicleTargetGeneratorSpeedLimits1_v();
	X1BWH_YawRateMonitoringActivation = Rte_Prm_X1BWH_YawRateMonitoringActivation_v();
	P10W3_Stfn_Axle5SuspVertStfns[0] = (*Rte_Prm_P10W3_Stfn_Axle5SuspVertStfns_v())[0];
	P10W3_Stfn_Axle5SuspVertStfns[1] = (*Rte_Prm_P10W3_Stfn_Axle5SuspVertStfns_v())[1];
	X1C4J_B_enaSlipCmp = Rte_Prm_X1C4J_B_enaSlipCmp_v();
	P10WX_Stfn_Axle2SuspVertStfns[0] = (*Rte_Prm_P10WX_Stfn_Axle2SuspVertStfns_v())[0];
	P10WX_Stfn_Axle2SuspVertStfns[1] = (*Rte_Prm_P10WX_Stfn_Axle2SuspVertStfns_v())[1];
	X1C3K_D_precTrsmOutpShaftSpdMeas = Rte_Prm_X1C3K_D_precTrsmOutpShaftSpdMeas_v();
	P1A7F_ConfigAxle_3_axle_type_liftable = Rte_Prm_P1A7F_ConfigAxle_3_axle_type_liftable_v();
	P1A8M_ConfigAxle_5_axle_type_steered = Rte_Prm_P1A8M_ConfigAxle_5_axle_type_steered_v();
	X1C9S_V_mtnDetnThdSpd = Rte_Prm_X1C9S_V_mtnDetnThdSpd_v();
	X1DBJ_A_mtnDetnThdLongAcc = Rte_Prm_X1DBJ_A_mtnDetnThdLongAcc_v();
	X1C3E_D_precLongVelRateInit = Rte_Prm_X1C3E_D_precLongVelRateInit_v();
	P1AFC_BrandType = Rte_Prm_P1AFC_BrandType_v();
	X1C49_Frq_lowSpdSnsrSelnSpdFilFrq = Rte_Prm_X1C49_Frq_lowSpdSnsrSelnSpdFilFrq_v();
	P1BGZ_SteeringRatioRight2 = Rte_Prm_P1BGZ_SteeringRatioRight2_v();
	X1DCG_B_enaAbsAsrDetn = Rte_Prm_X1DCG_B_enaAbsAsrDetn_v();
	P10V2_V_lowSpdSnsrSelnSpdThldUp = Rte_Prm_P10V2_V_lowSpdSnsrSelnSpdThldUp_v();
	P10WE_D_normSlipStfnAxle3 = Rte_Prm_P10WE_D_normSlipStfnAxle3_v();
	P1CNH_DistRA1ToRA2 = Rte_Prm_P1CNH_DistRA1ToRA2_v();
	X1C5C_D_lowSpdSnsrSelnYawRateScaFac = Rte_Prm_X1C5C_D_lowSpdSnsrSelnYawRateScaFac_v();
	X1C63_D_absTracCompLgtAScaFac = Rte_Prm_X1C63_D_absTracCompLgtAScaFac_v();
	P10VU_D_precLatJerkDueToBankAngleInput = Rte_Prm_P10VU_D_precLatJerkDueToBankAngleInput_v();
	X1C6V_D_FltHndlgIndirAltvSigFltScaFac = Rte_Prm_X1C6V_D_FltHndlgIndirAltvSigFltScaFac_v();
	P1A7B_ConfigAxle_2_axle_load_min = Rte_Prm_P1A7B_ConfigAxle_2_axle_load_min_v();
	P10W0_M_Axle4SuspVertLoads[0] = (*Rte_Prm_P10W0_M_Axle4SuspVertLoads_v())[0];
	P10W0_M_Axle4SuspVertLoads[1] = (*Rte_Prm_P10W0_M_Axle4SuspVertLoads_v())[1];
	X1C3A_L_trackWidthDrivenAxle = Rte_Prm_X1C3A_L_trackWidthDrivenAxle_v();
	P1A6A_ConfigAxle_1_axle_type_steered = Rte_Prm_P1A6A_ConfigAxle_1_axle_type_steered_v();
	P1A65_ConfigAxle_2_brake_factor = Rte_Prm_P1A65_ConfigAxle_2_brake_factor_v();
	X1C69_D_maxWheelSpeedTrustFac_vec[0] = (*Rte_Prm_X1C69_D_maxWheelSpeedTrustFac_vec_v())[0];
	X1C69_D_maxWheelSpeedTrustFac_vec[1] = (*Rte_Prm_X1C69_D_maxWheelSpeedTrustFac_vec_v())[1];
	X1C69_D_maxWheelSpeedTrustFac_vec[2] = (*Rte_Prm_X1C69_D_maxWheelSpeedTrustFac_vec_v())[2];
	X1C69_D_maxWheelSpeedTrustFac_vec[3] = (*Rte_Prm_X1C69_D_maxWheelSpeedTrustFac_vec_v())[3];
	X1C69_D_maxWheelSpeedTrustFac_vec[4] = (*Rte_Prm_X1C69_D_maxWheelSpeedTrustFac_vec_v())[4];
	X1C46_Tq_lowSpdSnsrSelnTqThldUp = Rte_Prm_X1C46_Tq_lowSpdSnsrSelnTqThldUp_v();
	P1A7W_ConfigAxle_3_axle_load_min = Rte_Prm_P1A7W_ConfigAxle_3_axle_load_min_v();
	P1BGW_SteeringRatioLeft1 = Rte_Prm_P1BGW_SteeringRatioLeft1_v();
	X1C5P_D_precWhlSpdMeas = Rte_Prm_X1C5P_D_precWhlSpdMeas_v();
	P1A6V_ConfigAxle_2_axle_type_steered = Rte_Prm_P1A6V_ConfigAxle_2_axle_type_steered_v();
	X1C5W_T_zeroSpdFltrTurnOffDly = Rte_Prm_X1C5W_T_zeroSpdFltrTurnOffDly_v();
	X1C8Z_D_wheelSpeedTrustFac_vec[0] = (*Rte_Prm_X1C8Z_D_wheelSpeedTrustFac_vec_v())[0];
	X1C8Z_D_wheelSpeedTrustFac_vec[1] = (*Rte_Prm_X1C8Z_D_wheelSpeedTrustFac_vec_v())[1];
	X1C8Z_D_wheelSpeedTrustFac_vec[2] = (*Rte_Prm_X1C8Z_D_wheelSpeedTrustFac_vec_v())[2];
	X1C8Z_D_wheelSpeedTrustFac_vec[3] = (*Rte_Prm_X1C8Z_D_wheelSpeedTrustFac_vec_v())[3];
	X1C8Z_D_wheelSpeedTrustFac_vec[4] = (*Rte_Prm_X1C8Z_D_wheelSpeedTrustFac_vec_v())[4];
	P1CNJ_DistRA2ToRA3 = Rte_Prm_P1CNJ_DistRA2ToRA3_v();
	P10WH_L_imuToFrontAxle = Rte_Prm_P10WH_L_imuToFrontAxle_v();
	P10W1_Stfn_Axle4SuspVertStfns[0] = (*Rte_Prm_P10W1_Stfn_Axle4SuspVertStfns_v())[0];
	P10W1_Stfn_Axle4SuspVertStfns[1] = (*Rte_Prm_P10W1_Stfn_Axle4SuspVertStfns_v())[1];
	P1A78_ConfigAxle_4_wh_rollingcircu = Rte_Prm_P1A78_ConfigAxle_4_wh_rollingcircu_v();
	P10WS_L_maxCogHeightFullyLaden = Rte_Prm_P10WS_L_maxCogHeightFullyLaden_v();
	P1K5K_E_EbsSwPackage = Rte_Prm_P1K5K_E_EbsSwPackage_v();
	X1C4U_B_enaLowSpdSnsrSeln = Rte_Prm_X1C4U_B_enaLowSpdSnsrSeln_v();
	P10WV_Stfn_Axle1SuspVertStfns[0] = (*Rte_Prm_P10WV_Stfn_Axle1SuspVertStfns_v())[0];
	P10WV_Stfn_Axle1SuspVertStfns[1] = (*Rte_Prm_P10WV_Stfn_Axle1SuspVertStfns_v())[1];
	X1C47_Tq_lowSpdSnsrSelnTqThldLo = Rte_Prm_X1C47_Tq_lowSpdSnsrSelnTqThldLo_v();
	P1A7X_ConfigAxle_3_axle_load_max = Rte_Prm_P1A7X_ConfigAxle_3_axle_load_max_v();
	P1A6K_ConfigAxle_1_brake_factor = Rte_Prm_P1A6K_ConfigAxle_1_brake_factor_v();
	X1DCF_T_mtnLowConfTolrTi = Rte_Prm_X1DCF_T_mtnLowConfTolrTi_v();
	P1A6Q_ConfigAxle_1_axle_load_min = Rte_Prm_P1A6Q_ConfigAxle_1_axle_load_min_v();
	P1CSH_FrontAxleArrangement = Rte_Prm_P1CSH_FrontAxleArrangement_v();
	P1A82_ConfigAxle_5_axle_load_min = Rte_Prm_P1A82_ConfigAxle_5_axle_load_min_v();
	X1DBH_D_precLatAccDueToBankAngleInit = Rte_Prm_X1DBH_D_precLatAccDueToBankAngleInit_v();
	P10VX_D_precLatAccMeas = Rte_Prm_P10VX_D_precLatAccMeas_v();
	X1C6T_D_FltHndlgAltvSigFltScaFac = Rte_Prm_X1C6T_D_FltHndlgAltvSigFltScaFac_v();
	P11DU_E_BusAxleType = Rte_Prm_P11DU_E_BusAxleType_v();
	P1B8V_VehicleTargetGeneratorSpeedLimits2 = Rte_Prm_P1B8V_VehicleTargetGeneratorSpeedLimits2_v();
	X1DBQ_D_absTracCompLongJerkScaFac = Rte_Prm_X1DBQ_D_absTracCompLongJerkScaFac_v();
	X1C5A_D_lowSpdSnsrSelnLgtAScaFac = Rte_Prm_X1C5A_D_lowSpdSnsrSelnLgtAScaFac_v();
	X1C61_T_interventionRampUpTime = Rte_Prm_X1C61_T_interventionRampUpTime_v();
	P10VS_D_precLongJerkInput = Rte_Prm_P10VS_D_precLongJerkInput_v();
	P1A8H_ConfigAxle_4_axle_load_min = Rte_Prm_P1A8H_ConfigAxle_4_axle_load_min_v();
	P1KME_DistFA1ToFA2 = Rte_Prm_P1KME_DistFA1ToFA2_v();
	X1DBO_D_absTracCompLatAScaFac = Rte_Prm_X1DBO_D_absTracCompLatAScaFac_v();
	X1C5T_D_lowSpdSnsrSelnLgtJerkScaFacSpd = Rte_Prm_X1C5T_D_lowSpdSnsrSelnLgtJerkScaFacSpd_v();
	P10WY_M_Axle3SuspVertLoads[0] = (*Rte_Prm_P10WY_M_Axle3SuspVertLoads_v())[0];
	P10WY_M_Axle3SuspVertLoads[1] = (*Rte_Prm_P10WY_M_Axle3SuspVertLoads_v())[1];
	P1A8B_ConfigAxle_4_brake_factor = Rte_Prm_P1A8B_ConfigAxle_4_brake_factor_v();
	X1C8W_B_enaWheelDeselection = Rte_Prm_X1C8W_B_enaWheelDeselection_v();
	X1DU0_T_absAsrDetnDelayTime = Rte_Prm_X1DU0_T_absAsrDetnDelayTime_v();
	P1A7G_ConfigAxle_3_axle_type_steered = Rte_Prm_P1A7G_ConfigAxle_3_axle_type_steered_v();
	X1C3F_D_precYawRateInit = Rte_Prm_X1C3F_D_precYawRateInit_v();
	P1A6H_ConfigAxle_1_wh_rollingcircu = Rte_Prm_P1A6H_ConfigAxle_1_wh_rollingcircu_v();
	P1A70_ConfigAxle_4_axle_type_liftable = Rte_Prm_P1A70_ConfigAxle_4_axle_type_liftable_v();
	X1DCH_A_whlRateAbsAsrDetnThd = Rte_Prm_X1DCH_A_whlRateAbsAsrDetnThd_v();
	P1A8V_ConfigAxle_5_p_thres = Rte_Prm_P1A8V_ConfigAxle_5_p_thres_v();
	P1A7P_ConfigAxle_3_p_thres = Rte_Prm_P1A7P_ConfigAxle_3_p_thres_v();
	P1RPH_NetworkArchitecture = Rte_Prm_P1RPH_NetworkArchitecture_v();
	P10VY_D_precYawRateMeas = Rte_Prm_P10VY_D_precYawRateMeas_v();
	X1C5D_D_lowSpdSnsrSelnTrsmSpdScaFac = Rte_Prm_X1C5D_D_lowSpdSnsrSelnTrsmSpdScaFac_v();
	P1CSI_TagAxleFeatures = Rte_Prm_P1CSI_TagAxleFeatures_v();
	P10WF_D_normSlipStfnAxle4 = Rte_Prm_P10WF_D_normSlipStfnAxle4_v();
	X1C62_B_enaTracComp = Rte_Prm_X1C62_B_enaTracComp_v();
	X1DBP_D_absTracCompYawRateScaFac = Rte_Prm_X1DBP_D_absTracCompYawRateScaFac_v();
	X1C7C_V_maxWheelSpeedTrustBreakPoints_vec[0] = (*Rte_Prm_X1C7C_V_maxWheelSpeedTrustBreakPoints_vec_v())[0];
	X1C7C_V_maxWheelSpeedTrustBreakPoints_vec[1] = (*Rte_Prm_X1C7C_V_maxWheelSpeedTrustBreakPoints_vec_v())[1];
	X1C7C_V_maxWheelSpeedTrustBreakPoints_vec[2] = (*Rte_Prm_X1C7C_V_maxWheelSpeedTrustBreakPoints_vec_v())[2];
	X1C7C_V_maxWheelSpeedTrustBreakPoints_vec[3] = (*Rte_Prm_X1C7C_V_maxWheelSpeedTrustBreakPoints_vec_v())[3];
	X1C7C_V_maxWheelSpeedTrustBreakPoints_vec[4] = (*Rte_Prm_X1C7C_V_maxWheelSpeedTrustBreakPoints_vec_v())[4];
	X1C5U_Frq_lowSpdSnsrSelnSpdFilFrq = Rte_Prm_X1C5U_Frq_lowSpdSnsrSelnSpdFilFrq_v();
	P10WZ_Stfn_Axle3SuspVertStfns[0] = (*Rte_Prm_P10WZ_Stfn_Axle3SuspVertStfns_v())[0];
	P10WZ_Stfn_Axle3SuspVertStfns[1] = (*Rte_Prm_P10WZ_Stfn_Axle3SuspVertStfns_v())[1];
	X1C29_L_trackWidthNonDrivenAxle = Rte_Prm_X1C29_L_trackWidthNonDrivenAxle_v();
	X1C8X_Tq_minTotalBrakeTorque = Rte_Prm_X1C8X_Tq_minTotalBrakeTorque_v();
	X1C3G_D_precYawAccInit = Rte_Prm_X1C3G_D_precYawAccInit_v();
	P1A64_ConfigAxle_2_p_thres = Rte_Prm_P1A64_ConfigAxle_2_p_thres_v();
	P1E5Z_Radar2FrontAxleDist = Rte_Prm_P1E5Z_Radar2FrontAxleDist_v();
	P1A8W_ConfigAxle_5_brake_factor = Rte_Prm_P1A8W_ConfigAxle_5_brake_factor_v();
	P10WC_D_normSlipStfnAxle1 = Rte_Prm_P10WC_D_normSlipStfnAxle1_v();
	X1DCI_Frq_whlRateFilFrq = Rte_Prm_X1DCI_Frq_whlRateFilFrq_v();
	X1C5Q_D_lowSpdSnsrSelnLgtJerkScaFacTrq = Rte_Prm_X1C5Q_D_lowSpdSnsrSelnLgtJerkScaFacTrq_v();
	P10WR_L_minCogHeightUnladen = Rte_Prm_P10WR_L_minCogHeightUnladen_v();
	X1C80_V_speedDifferenceBreakPoints_vec[0] = (*Rte_Prm_X1C80_V_speedDifferenceBreakPoints_vec_v())[0];
	X1C80_V_speedDifferenceBreakPoints_vec[1] = (*Rte_Prm_X1C80_V_speedDifferenceBreakPoints_vec_v())[1];
	X1C80_V_speedDifferenceBreakPoints_vec[2] = (*Rte_Prm_X1C80_V_speedDifferenceBreakPoints_vec_v())[2];
	X1C80_V_speedDifferenceBreakPoints_vec[3] = (*Rte_Prm_X1C80_V_speedDifferenceBreakPoints_vec_v())[3];
	X1C80_V_speedDifferenceBreakPoints_vec[4] = (*Rte_Prm_X1C80_V_speedDifferenceBreakPoints_vec_v())[4];
	P1IJ3_EquivalentWheelbaseTurning = Rte_Prm_P1IJ3_EquivalentWheelbaseTurning_v();
	X1DCM_A_whlRateAbsAsrRstThd = Rte_Prm_X1DCM_A_whlRateAbsAsrRstThd_v();
	X1C3D_D_precLongVelInit = Rte_Prm_X1C3D_D_precLongVelInit_v();
	P1AT2_SelfSteeredTagAxleSpeedHysteresis = Rte_Prm_P1AT2_SelfSteeredTagAxleSpeedHysteresis_v();
	P10WT_AgV_maxPitchRate = Rte_Prm_P10WT_AgV_maxPitchRate_v();
	P10WW_M_Axle2SuspVertLoads[0] = (*Rte_Prm_P10WW_M_Axle2SuspVertLoads_v())[0];
	P10WW_M_Axle2SuspVertLoads[1] = (*Rte_Prm_P10WW_M_Axle2SuspVertLoads_v())[1];
	P1BGX_SteeringRatioLeft2 = Rte_Prm_P1BGX_SteeringRatioLeft2_v();
	X1C9T_V_mtnDetnHysSpd = Rte_Prm_X1C9T_V_mtnDetnHysSpd_v();
	X1C6Z_B_enaAbsComp = Rte_Prm_X1C6Z_B_enaAbsComp_v();
	P1BGY_SteeringRatioRight1 = Rte_Prm_P1BGY_SteeringRatioRight1_v();
	P10V1_V_lowSpdSnsrSelnSpdThldLo = Rte_Prm_P10V1_V_lowSpdSnsrSelnSpdThldLo_v();
	P1A8T_ConfigAxle_5_wh_rollingcircu = Rte_Prm_P1A8T_ConfigAxle_5_wh_rollingcircu_v();
	P1A0N_B_EspNotAvailable = Rte_Prm_P1A0N_B_EspNotAvailable_v();
	P1AZQ_WheelBase = Rte_Prm_P1AZQ_WheelBase_v();
	P1E50_VehicleWidth_mm = Rte_Prm_P1E50_VehicleWidth_mm_v();
	P1M6I_NoOfPulsesPerRevolution = Rte_Prm_P1M6I_NoOfPulsesPerRevolution_v();
	P1C54_FactoryModeActive = Rte_Prm_P1C54_FactoryModeActive_v();
};
#endif
