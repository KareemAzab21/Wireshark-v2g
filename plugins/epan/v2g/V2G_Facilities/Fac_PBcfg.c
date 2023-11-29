// /******************************************************************************
// *
// * Module: Fac
// *
// * File Name: Fac_PBcfg.c
// *
// * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Fac Driver
// *
// * Author:Omar Reda - Aly Maamoun - Youssef Hussein - Tasneem Essamt
// ******************************************************************************/
//
//#include "Fac.h"
//
//
//const Fac_ConfigType Fac_Configuration = {
//
//	{ /* supportedAppProtocolReq */
//
//		{/* Appprotocol */
//
//
//			{ /* array of structures */
//
//				{ /* first structure element */
//
//					{/* ProtocolNamespace */
//
//						{/* characters */
//							'u','r','n',':','i','s','o',':','1','5','1','1','8',':','2',':','2','0','1','0',':','M','s','g','D','e','f'
//						},/* characters */
//
//						{/* charactersLen */
//							27
//						}/* charactersLen */
//
//					},/* ProtocolNamespace */
//
//					{ /* VersionNumberMajor */
//						1
//					}, /* VersionNumberMajor */
//
//					{ /* VersionNumberMinor */
//						0
//					}, /* VersionNumberMinor */
//
//					{ /* SchemaID */
//						1
//					}, /* SchemaID */
//
//					{ /* Priority */
//						1
//					}, /* Priority */
//
//				}, /* first structure element */
//
//
//
//				{ /* second structure element */
//
//					{/* ProtocolNamespace */
//
//						{/* characters */
//							'u','r','n',':','d','i','n',':','7','0','1','2','1',':','2',':','2','0','1','2',':','M','s','g','D','e','f'
//						},/* characters */
//
//						{/* charactersLen */
//							27
//						}/* charactersLen */
//
//					},/* ProtocolNamespace */
//
//					{ /* VersionNumberMajor */
//						1
//					}, /* VersionNumberMajor */
//
//					{ /* VersionNumberMinor */
//						0
//					}, /* VersionNumberMinor */
//
//					{ /* SchemaID */
//						2
//					}, /* SchemaID */
//
//					{ /* Priority */
//						2
//					}, /* Priority */
//
//				} /* second structure element */
//
//			}, /* array of structures */
//
//
//			{ /* arraylength */
//				2
//			} /* arraylength  */
//
//		}/* Appprotocol */
//
//
//	},/* supportedAppProtocolReq */
//
//
//
//
//
//
//
//	{ /* SessionSetupReq */
//
//		{/* EVCCID struct */
//
//			/*bytes array , bytesLen*/
//			 {10}		  ,1
//		}
//	},/* SessionSetupReq*/
//
//
//
//
//
//
//	{ /* ServiceDiscoveryReq */
//
//		{/*SupportedServiceIDs struct*/
//
//			{/*ServiceID struct */
//				/*array , arrayLen*/
//				 {1}	, 1
//
//			}
//			/*ServiceID struct */
//
//		}
//		/*SupportedServiceIDs struct*/
//
//		,1 /*unsigned int SupportedServiceIDs_isUsed*/
//
//	},/* ServiceDiscoveryReq */
//
//
//
//
//
//
//	{
//		iso2paymentOptionType_ExternalPayment
//	},
//
//
//
///*	{
//		1,
//		{
//
//
//			 1		   , 4
//		},
//
//		{},0
//	}, */
//
//
//
//
//	{ /* PaymentDetailsReq */
//		{ /* eMaid */
//		/* array */		/* arraylen */
//			{1, 123}	,	 2
//		} /* eMaid */
//		,
//		{ /* iso2CertificateChainType ContractSignatureCertChain */
//			{ /* Id */
//			   /* array */			/* characterslen */
//				{ 'I' , 'D' }	,		 2
//			} /* Id */
//			,
//			1 /* ID is_used */
//			,
//			{ /* Certificate */
//				/* array */        /*characterslen */
//				{ 'C' , 'E' } 	,	2
//			} /* Certificate */
//			,
//			{ /* subcertificates */
//				{ /* certificate */
//
//				{		/* arr0 */										/* arr1 */
//				       /* bytes */  /* byteslen */					/*bytes*/	/*byteslen*/
//					{  { 'S' , 'U'} , 2 } 		, 			{ {'S' , 'U' , '2'}  , 3      }
//				}    ,  2   /* arraylen */
//
//				} /* certificate */
//			} /* subcertificates */
//			,
//			1 /* subcertificates is used */
//
//
//
//
//		} /* iso2CertificateChainType ContractSignatureCertChain */
//
//	},/* PaymentDetailsReq */
//
//
//
//
//
//
//	{ /* ChargeParameterDiscoveryReq */
//		1234,										//MaxSupportingPoints 												//1
//		0,//preconfing for isused parameter 		//MaxSupportingPoints_isUsed										//2
//		{											/*iso2EVEnergyTransferParameterType*/								//3
//			0 //departure time must be dynamic		//DepartureTime
//		},											/*iso2EVEnergyTransferParameterType*/
//		0,//preconfing for isused parameter 		//EVEnergyTransferParameter_isUsed									//4
//		{											/*iso2AC_EVChargeParameterType*/									//5
//			0,										//DepartureTime														//0
//			{										/*iso2PhysicalValueType EVMaximumChargePower*/						//a
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMaximumChargePower*/
//			{										/*iso2PhysicalValueType EVMaximumChargeCurrent*/ 					//b
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMaximumChargeCurrent*/
//			{										/*iso2PhysicalValueType EVMinimumChargeCurrent*/ 					//c
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMinimumChargeCurrent*/
//			{										/*iso2PhysicalValueType EVTargetEnergyRequest*/						//d
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVTargetEnergyRequest*/
//			0,										//EVTargetEnergyRequest_isUsed:1									//e
//			{										/*iso2PhysicalValueType EVMaximumEnergyRequest*/ 					//f
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMaximumEnergyRequest*/
//			0,										//EVMaximumEnergyRequest_isUsed    									//g
//			{										/*iso2PhysicalValueType EVMinimumEnergyRequest*/					//h
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMinimumEnergyRequest*/
//			0,										//EVMinimumEnergyRequest_isUsed										//i
//			{										/*iso2PhysicalValueType EVMaximumVoltage*/							//j
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMaximumVoltage*/
//		},											/*iso2AC_EVChargeParameterType*/
//		0,											//AC_EVChargeParameter_isUsed										//6
//		{											/* AC_EVBidirectionalParameter*/									//7
//			0,										//DepartureTime														//0a
//			{										/*iso2PhysicalValueType EVMaximumChargePower*/						//0b
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMaximumChargePower*/
//			{										/*iso2PhysicalValueType EVMaximumChargeCurrent*/					//0c
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMaximumChargeCurrent*/
//			{										/*iso2PhysicalValueType EVMinimumChargeCurrent*/					//0d
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMinimumChargeCurrent*/
//			{										/*iso2PhysicalValueType EVTargetEnergyRequest*/						//0e
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVTargetEnergyRequest*/
//			0,										//EVTargetEnergyRequest_isUsed										//0f
//			{										/*iso2PhysicalValueType EVMaximumEnergyRequest*/					//0g
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMaximumEnergyRequest*/
//			0,										//EVMaximumEnergyRequest_isUsed										//0h
//			{										/*iso2PhysicalValueType EVMinimumEnergyRequest*/					//0i
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMinimumEnergyRequest*/
//			0,										//EVMinimumEnergyRequest_isUsed										//0j
//			{										/*iso2PhysicalValueType EVMaximumVoltage*/							//0k
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMaximumVoltage*/
//			{										/*iso2PhysicalValueType EVMaximumDischargePower*/					//0l
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMaximumDischargePower*/
//			{										/*iso2PhysicalValueType EVMaximumDischargeCurrent*/					//0m
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMaximumDischargeCurrent*/
//			{										/*iso2PhysicalValueType EVMinimumDischargeCurrent*/					//0n
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMinimumDischargeCurrent*/
//		},											/* AC_EVBidirectionalParameter*/
//		0,											//AC_EVBidirectionalParameter_isUsed								//8
//		{											/*iso2DC_EVChargeParameterType DC_EVChargeParameter*/				//9
//			0,										//DepartureTime	must be dynamic										//1a
//			{										/*iso2PhysicalValueTypeEVMaximumChargePower */						//1b
//				0,									//Exponent
//				100									//Value
//			},										/*iso2PhysicalValueTypeEVMaximumChargePower */
//			0,										//EVMaximumChargePower_isUsed										//1c
//			{										/*iso2PhysicalValueType EVMinimumChargePower*/						//1d
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMinimumChargePower*/
//			0,										//EVMinimumChargePower_isUsed										//1e
//			{										/*iso2PhysicalValueType EVMaximumChargeCurrent*/					//1f
//				0,									//Exponent
//				400,								//Value
//			},										/*iso2PhysicalValueType EVMaximumChargeCurrent*/
//			{										/*iso2PhysicalValueType EVMinimumChargeCurrent*/					//1g
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMinimumChargeCurrent*/
//			{										/*iso2PhysicalValueType EVMaximumVoltage*/							//1h
//				0,									//Exponent
//				400,								//Value
//			},										/*iso2PhysicalValueType EVMaximumVoltage*/
//			{										/*iso2PhysicalValueType EVTargetEnergyRequest*/						//1i
//				2,									//Exponent
//				200,								//Value
//			},										/*iso2PhysicalValueType EVTargetEnergyRequest*/
//			0,										//EVTargetEnergyRequest_isUsed										//1j
//			{										/*iso2PhysicalValueType EVMaximumEnergyRequest*/					//1k
//				2,									//Exponent
//				200,								//Value
//			},										/*iso2PhysicalValueType EVMaximumEnergyRequest*/
//			0,										//EVMaximumEnergyRequest_isUsed										//1l
//			{										/*iso2PhysicalValueType EVMinimumEnergyRequest*/					//1m
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMinimumEnergyRequest*/
//			0,										//EVMinimumEnergyRequest_isUsed										//1n
//			0,										//CurrentSOC														//1o
//			0,										//CurrentSOC_isUsed													//1r
//			0,										//TargetSOC															//1q
//			0,										//TargetSOC_isUsed													//1t
//			0,										//BulkSOC															//1s
//			0,										//BulkSOC_isUsed													//1u
//		},											/*iso2DC_EVChargeParameterType DC_EVChargeParameter*/
//		0,											//DC_EVChargeParameter_isUsed										//10
//		{											/*iso2DC_EVBidirectionalParameterType DC_EVBidirectionalParameter*/ //11
//			0,										//DepartureTime														//2a
//			{										/*iso2PhysicalValueType EVMaximumChargePower*/						//2b
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVMaximumChargePower*/
//			0,										//EVMaximumChargePower_isUsed										//2c
//			{										/*iso2PhysicalValueType EVMinimumChargePower*/						//2d
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVMinimumChargePower*/
//			0,										//EVMinimumChargePower_isUsed										//2e
//			{										/*iso2PhysicalValueType EVMaximumChargeCurrent*/					//2f
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVMaximumChargeCurrent*/
//			{										/*iso2PhysicalValueType EVMinimumChargeCurrent*/					//2g
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVMinimumChargeCurrent*/
//			{										/*iso2PhysicalValueType EVMaximumVoltage*/							//2h
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVMaximumVoltage*/
//			{										/*iso2PhysicalValueType EVTargetEnergyRequest*/						//2i
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVTargetEnergyRequest*/
//			0,										//EVTargetEnergyRequest_isUsed										//2j
//			{										/*iso2PhysicalValueType EVMaximumEnergyRequest*/					//2k
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVMaximumEnergyRequest*/
//			0,										//EVMaximumEnergyRequest_isUsed										//2l
//			{										/*iso2PhysicalValueType EVMinimumEnergyRequest*/					//2m
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVMinimumEnergyRequest*/
//			0,										//EVMinimumEnergyRequest_isUsed										//2m
//			0,										//CurrentSOC														//2o
//			0,										//CurrentSOC_isUsed													//2r
//			0,										//TargetSOC															//2q
//			0,										//TargetSOC_isUsed													//2t
//			0,										//BulkSOC															//2s
//			0,										//BulkSOC_isUsed													//2u
//			{										/*iso2PhysicalValueType EVMaximumDischargePower*/					//2v
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVMaximumDischargePower*/
//			0,										//EVMaximumDischargePower_isUsed									//2w
//			{										/*iso2PhysicalValueType EVMinimumDischargePower*/					//2x
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVMinimumDischargePower*/
//			0,										//EVMinimumDischargePower_isUsed									//2y
//			{										/*iso2PhysicalValueType EVMaximumDischargeCurrent*/					//2z
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVMaximumDischargeCurrent*/
//			{										/*iso2PhysicalValueType EVMinimumDischargeCurrent*/					//2p
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVMinimumDischargeCurrent*/
//			{										/*iso2PhysicalValueType EVMinimumVoltage*/							//22a
//				0,									//Exponent
//				0,									//Value
//			},										/*iso2PhysicalValueType EVMinimumVoltage*/
//			0,										//MinimumSOC														//22b
//			0										//MinimumSOC_isUsed													//22c
//		},											/*iso2DC_EVBidirectionalParameterType DC_EVBidirectionalParameter*/
//		0,											//DC_EVBidirectionalParameter_isUsed								//12
//		{											/*iso2WPT_EVChargeParameterType*/									//13
//			0,										//DepartureTime														//3a
//			{										/*iso2PhysicalValueType EVMaximumPower*/							//3b
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMaximumPower*/
//			{										/*iso2PhysicalValueType EVMinimumPower*/							//3c
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMinimumPower*/
//			{										/*iso2PhysicalValueType EVTargetEnergyRequest*/						//3d
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVTargetEnergyRequest*/
//			0,										//EVTargetEnergyRequest_isUsed										//3e
//			{										/*iso2PhysicalValueType EVMaximumEnergyRequest*/					//3f
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMaximumEnergyRequest*/
//			0,										//EVMaximumEnergyRequest_isUsed										//3g
//			{										/*iso2PhysicalValueType EVMinimumEnergyRequest*/					//3h
//				0,									//Exponent
//				0									//Value
//			},										/*iso2PhysicalValueType EVMinimumEnergyRequest*/
//			0,										//EVMinimumEnergyRequest											//3i
//		},											/*iso2WPT_EVChargeParameterType*/
//		0,											//WPT_EVChargeParameter_isUsed										//14
//		{											/*iso2MinimumPMaxRequestType MinimumPMaxRequest */					//15
//			{										/*MinimumPMaxScheduleEntry*/										//4a
//				0,									/*iso2PMaxScheduleEntryType*/										//4b
//				0									//arrayLen															//4c
//			},
//		},											/*iso2MinimumPMaxRequestType MinimumPMaxRequest */
//		0											//MinimumPMaxRequest_isUsed											//16
//	},/* ChargeParameterDiscoveryReq */
//
//
//
//
//
//	{ /* PreChargeReq */
//
//		{ /* iso2PhysicalValueType : EVTargetVoltage */
//		  /* Value */     /* exponent */
//			1		,		234
//		} /* iso2PhysicalValueType : EVTargetVoltage*/
//		,
//		{ /* iso2PhysicalValueType : EVTargetCurrent */
//		 /* Value */     /* exponent */
//			1 		, 		100
//		} /* iso2PhysicalValueType : EVTargetCurrent */
//
//	},/* PreChargeReq */
//
//
//
//	{ /* SessionStopReqType */
//		iso2chargingSessionType_Pause
//	}/* SessionStopReqType */
//
//
//
//
//
//
//
//
//
//};
//
//
//
//
//
//
//
//
//
//
