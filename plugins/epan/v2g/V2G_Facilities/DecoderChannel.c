/*******************************************************************
 *
 * @author : Youssef Hussien and Tasneem Essmat
 * @version 20-10-2022
 * @contact: ysfhussien@gmail.com
 *			 tasneemessmat@gmail.com
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 * File Name: DecoderChannel.c
 * Description: This is an Decoder channel containing decoding functions for every data type.
 ********************************************************************/


/*------------------------------------- File Includes ------------------------------------- */

#include "DecoderChannel.h"
#include "EXIConfig.h"
#include "EXIOptions.h"
#include "BitInputStream.h"
#include "EXITypes.h"
#include "MethodsBag.h"
#include "ErrorCodes.h"

#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
#include "DynamicMemory.h"
#endif /* DYNAMIC_ALLOCATION */

#ifndef DECODER_CHANNEL_C
#define DECODER_CHANNEL_C


/*----------------------------------------- # Defines ------------------------------------- */
/* unsigned long == 64 bits, 10 * 7bits = 70 bits */
#define MAX_OCTETS_FOR_UNSIGNED_INTEGER_64 10
/* unsigned int == 32 bits, 5 * 7bits = 35 bits */
#define MAX_OCTETS_FOR_UNSIGNED_INTEGER_32 5

/*------------------------------------- Golabal Variables ---------------------------------- */
/* buffer for reading (arbitrary) large integer values */
static uint8_t maskedOctets[MAX_OCTETS_FOR_UNSIGNED_INTEGER_64];




/************************************************************************************
* Service Name: _decodeUnsignedInteger
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to iv structure , sign of decoded data
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
static int _decodeUnsignedInteger(bitstream_t* stream, exi_integer_t* iv, int negative) {
	/* Flag to indicate that there is an error or not */
	int errn = 0;

	/* Declare i to be used in illetrations */
	int i = 0;

	/* Temprory Variable to read bits in */
	uint8_t b;

	/* Declare k to be used in Illetrations */
	int k;

	/* Read the octets in the global variable */
	do {
		/* Read the next octet */
		errn = decode(stream, &b);

		/* Check if there is an error from the decode step */
		if (errn == 0) {

			if(i < MAX_OCTETS_FOR_UNSIGNED_INTEGER_64) {
				/* the 7 least significant bits hold the actual value */
				maskedOctets[i++] = (b & 127);

			} else {
				/* Report an Error of Unsupported integar value */
				errn = EXI_UNSUPPORTED_INTEGER_VALUE;
			}
		}
	} while( errn == 0 && b >= 128 ); /* no more octets ? */

	/* check if there is an error from the reading step */
	if ( errn == 0 ) {

		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */

		/* Switch case on illetration number */
		switch(i) {

		/* Case 1: 7 bits only */
		case 1:

			/* in case negative, assign the negative value to the EXI struct */
			if (negative) {
				iv->val.int8 =  (int8_t)(-( b + 1));
				iv->type = EXI_INTEGER_8;

			/* in case postive, assign the postive value to the EXI struct */
			} else {
				iv->val.uint8 = b;
				iv->type = EXI_UNSIGNED_INTEGER_8;
			}
			break;

		/* Case 2: 14 bits only */
		case 2:

			/* initialize the unint16 */
			iv->val.uint16 = 0;

			/* illetrate 2 times to have the 2 octets and assign the value to the unint16 */
			for (k = i-1; k >= 0 ; k--) {
				iv->val.uint16  = (uint16_t)((iv->val.uint16 << 7) | maskedOctets[k]);
			}

			/* In case Negative, assign the negative value to the EXI Struct */
			if (negative) {
				iv->val.int16 = (int16_t)( -( iv->val.uint16 + 1 ));
				iv->type = EXI_INTEGER_16;

			/* in case postive, assign the type to EXI Struct */
			} else {
				iv->type = EXI_UNSIGNED_INTEGER_16;
			}
			break;

		/* Case 3: 21 bits only, Pass the case to reach 28 bits case 4 */
		case 3:

		/* Case 4: 28 bits */
		case 4:

			/* initialize the unint32 */
			iv->val.uint32 = 0;

			/* illetrate 4 times to have the 4 octets and assign value to uint32 */
			for (k = i-1; k >= 0 ; k--) {
				iv->val.uint32 = (iv->val.uint32 << 7) | maskedOctets[k];
			}

			/* In case Negative, assign the negative value to the EXI Struct */
			if (negative) {
				iv->val.int32 = (-(int32_t)(iv->val.uint32 + 1));

				/* check if the value can be assigned to 16 bits only */
				if (iv->val.int32 <= INT16_MAX && iv->val.int32 >= INT16_MIN ) {

					/* Assign the EXI Struct type to int16 */
					iv->type = EXI_INTEGER_16;

				/* Assign the EXI Struct type to int32 */
				} else {
					iv->type = EXI_INTEGER_32;
				}


			/* in case postive, assign the type to EXI Struct */
			} else {

				/* Check if the value can be assigned to 16 bits only */
				if (iv->val.uint32 <= UINT16_MAX) {

					/* assign the EXI struct type to unsigned int 16 */
					iv->type = EXI_UNSIGNED_INTEGER_16;

				/* assign the EXI struct type to unsigned int 32 */
				} else {
					iv->type = EXI_UNSIGNED_INTEGER_32;
				}
			}
			break;

        /* Case 5 : 35 bits, pass the case to reach case 10 octets to assign to 64 bit */
		case 5:

	    /* Case 6 : 42 bits, pass the case to reach case 10 octets to assign to 64 bit */
		case 6:

	    /* Case 7 : 49 bits, pass the case to reach case 10 octets to assign to 64 bit */
		case 7:

	    /* Case 8 : 56 bits, pass the case to reach case 10 octets to assign to 64 bit */
		case 8:

	    /* Case 9 : 63 bits, pass the case to reach case 10 octets to assign to 64 bit */
		case 9:

	    /* Case 10 : 35 to 70 bits */
		case 10:

			/* initialize the uint64 */
			iv->val.uint64 = 0;

			/* illetrate 10 times to have the 10 octets and assign the value to unint64 */
			for (k = i-1; k >= 0 ; k--) {
				iv->val.uint64  = (iv->val.uint64 << 7) | maskedOctets[k];
			}

			/* in case negative */
			if (negative) {

				/* Check if the number of octets can be assigned */
				if (i > 9) {

					/* in case larger than 9 octets, report error unsupported large integar value */
					return EXI_UNSUPPORTED_INTEGER_VALUE;
				}

				/* assign the negative value to int64 EXI struct */
				iv->val.int64 = (-(int64_t)(iv->val.uint64 + 1));

				/* check if the value can be assigned to 32 bit */
				if (iv->val.int64 <= INT32_MAX && iv->val.int64 >= INT32_MIN ) {

					/* change the EXI struct type to integar 32 */
					iv->type = EXI_INTEGER_32;

				/* if not, make the type assigned to integar 64 */
				} else {
					iv->type = EXI_INTEGER_64;
				}

			/* in case positive */
			} else {

				/* check if the value can be assigned to 32 bit */
				if (iv->val.uint64 <= UINT32_MAX) {

					/* change the type to unsigned integar 32 */
					iv->type = EXI_UNSIGNED_INTEGER_32;

				/* if not, make the type assigned to unsigned integar 64 */
				} else {
					iv->type = EXI_UNSIGNED_INTEGER_64;
				}
			}
			break;

		/* if non of the above cases, Report error due to unsupported integar value */
		default:
			errn = EXI_UNSUPPORTED_INTEGER_VALUE;
			break;
		}
	}


	/* return error code */
	return errn;
}





/************************************************************************************
* Service Name: decodeUnsignedInteger
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to iv structure.
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this function calls the _decodeUnsignedIntegar function, by passing 0
* 			   in sign argument indication postive data
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeUnsignedInteger(bitstream_t* stream, exi_integer_t* iv) {
	return _decodeUnsignedInteger(stream, iv, 0);
}




/************************************************************************************
* Service Name: decodeUnsignedInteger16
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to uint16 variable to write the decoded
* 				   data in it.
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this function decodes the unisgned integar 16 data type.
* 			   all the illustrated decoding steps are standarized from w3c EXI decoding.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeUnsignedInteger16(bitstream_t* stream, uint16_t* uint16) {

	/* initialize the number of shifts to 0 */
	unsigned int mShift = 0;

	/* initialize error code to zero */
	int errn = 0;

	/* temprory value to write decoded data in it */
	uint8_t b = 0;

	/* initialize the data variable we will write in */
	*uint16 = 0;

	/* start decoding per each octet */
	do {

		/* 1. Read the next octet */
		errn = decode(stream, &b);

		/* 2. Multiply the value of the unsigned number represented by the 7
		 * least significant
		 * bits of the octet by the current multiplier and add the result to
		 * the current value */
		*uint16 = (uint16_t)(*uint16 + ((b & 127) << mShift));

		/* 3. Multiply the multiplier by 128 */
		mShift += 7;

		/* 4. If the most significant bit of the octet was 1, go back to step 1 */
	} while (errn == 0 && (b >> 7) == 1);


	/* return the error code */
	return errn;
}



/************************************************************************************
* Service Name: decodeUnsignedInteger32
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to uint32 variable to write the decoded
* 				   data in it.
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this function decodes the unisgned integar 32 data type.
* 			   all the illustrated decoding steps are standarized from w3c EXI decoding.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeUnsignedInteger32(bitstream_t* stream, uint32_t* uint32) {
	/* 0XXXXXXX ... 1XXXXXXX 1XXXXXXX */

	/* initialize the number of shifts to 0 */
	unsigned int mShift = 0;

	/* initialize error code to zero */
	int errn = 0;

	/* Temprory variable to read the decoded data in it */
	uint8_t b = 0;

	/* initialize the variable we will write the decoded data in it */
	*uint32 = 0;


	/* start decoding per each octet */
	do {

		/* 1. Read the next octet */
		errn = decode(stream, &b);

		/* 2. Multiply the value of the unsigned number represented by the 7
		 * least significant
		 * bits of the octet by the current multiplier and add the result to
		 * the current value */
		*uint32 += (uint32_t)((b & 127) << mShift);

		/* 3. Multiply the multiplier by 128 */
		mShift += 7;

		/* 4. If the most significant bit of the octet was 1, go back to step 1 */
	} while (errn == 0 && (b >> 7) == 1);

	/* return the error code */
	return errn;
}






/************************************************************************************
* Service Name: decodeUnsignedIntegerSizeT
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, variable indicates the size.
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this function allowes decoding of variable sizes based on configurations
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeUnsignedIntegerSizeT(bitstream_t* stream, size_t* sizeT) {

	/* initialize error code to 0 */
	int errn = 0;

	/* if the SIZE max = 16 bits */
	if(SIZE_MAX == UINT16_MAX) {

		/* decclare 16bit temprory variable */
		uint16_t uint16;

		/* call dencodeUnsignedIntegar16 Function */
		errn = decodeUnsignedInteger16(stream, &uint16);

		/* in case no errors at decoding step, assign the value to sizeT */
		if(errn == 0) {
			*sizeT = (size_t)uint16;
		}

	/* if the SIZE max = 32 bits */
	} else if(SIZE_MAX == UINT32_MAX) {

		/* declare 32 bit temprory variable */
		uint32_t uint32;

		/* call decodeUnsignedInteger32 function */
		errn = decodeUnsignedInteger32(stream, &uint32);

		/* in case no errors at decoding step, assign the value to sizeT */
		if(errn == 0) {
			*sizeT = (size_t)uint32;
		}

	/* if the SIZE max = 64 bit */
	} else {

		/* declare 64 bit variable */
		uint64_t uint64;

		/* call decodeUnsignedIntegar64 Function */
		errn = decodeUnsignedInteger64(stream, &uint64);

		/* in case no errors in decoding step, assign value to sizeT */
		if(errn == 0) {
			*sizeT = (size_t)uint64;
		}
	}


	/* return the error code*/
	return errn;
}



/************************************************************************************
* Service Name: decodeUnsignedInteger64
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to uint64 variable to write the decoded
* 				   data in it.
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:  Decode an arbitrary precision non negative integer using a sequence of
				octets. The most significant bit of the last octet is set to zero to
				indicate sequence termination. Only seven bits per octet are used to
				store the integer's value.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeUnsignedInteger64(bitstream_t* stream, uint64_t* uint64) {

	/* initialize the number of shifts to 0 */
	unsigned int mShift = 0;

	/* initilize error code to 0 */
	int errn = 0;

	/* declare temprory variable to store data in it */
	uint8_t b;

	/* initilize the variable we will write data in it */
	*uint64 = 0L;


	/* start decoding per each octet */
	do {

		/* 1. Read the next octet */
		errn = decode(stream, &b);

		/* 2. Multiply the value of the unsigned number represented by the 7
		 * least significant
		 * bits of the octet by the current multiplier and add the result to
		 * the current value */
		*uint64 += ((uint64_t) (b & 127)) << mShift;

		/* 3. Multiply the multiplier by 128 */
		mShift += 7;

	/* 4. If the most significant bit of the octet was 1, go back to step 1 */
	} while (errn == 0 && (b >> 7) == 1);


	/* Return the error code */
	return errn;
}



/************************************************************************************
* Service Name: _reverseArray
* Service ID[hex]: none
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to array, number of reverses.
* Parameters (inout): None
* Parameters (out): None
* Return value: void
* Description:  this is an internally used function, called inside DecodeunsignedIntegerBig
* Available via: None
* Requirement:
************************************************************************************/
void _reverseArray(uint8_t *array, int number) {
	/* declare 2 variables */
    int x, t;

    /* -- number to maintain number of illetrations */
    number--;

    /* illetrate to the array */
    for(x = 0; x < number; x ++, number --) {
        t = array[x];
        array[x] = array[number];
        array[number] = t;
    }
}


/************************************************************************************
* Service Name: decodeUnsignedIntegerBig
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, size , pointer to array of data to write decoded data in it, leng
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode an arbitrary precision non negative integer using a sequence of
				 octets. The most significant bit of the last octet is set to zero to
 	 	 	 	 indicate sequence termination. Only seven bits per octet are used to
                 store the integer's value.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeUnsignedIntegerBig(bitstream_t* stream, size_t size, uint8_t* data, size_t* len) {

	/* intialize error code to 0*/
	int errn = 0;

	/* initialize temprory variable to write data in it */
	uint8_t b = 0;

	/* initialize number of shifts to zero in all phases */
	unsigned int mShift1 = 0;
	unsigned int mShift2 = 0;
	unsigned int mShift3 = 0;
	unsigned int mShift4 = 0;

	/* initialize number if bytes read to 0*/
	unsigned int nBytesRead = 0;

	/* initialize bits avilable to 0 */
	unsigned int nBitsAvailable = 0;

	/* initialize varibles to put data in it */
	uint64_t uint64_1 = 0;
	uint64_t uint64_2 = 0;
	uint64_t uint64_3 = 0;
	uint64_t uint64_4 = 0;

	/* initialize lenght to zero */
	*len = 0;

	do {

		/* 1. decode the next octet */
		errn = decode(stream, &b);

		/* increment read bytes */
		nBytesRead++;

		/* increments bits available by 7 */
		nBitsAvailable += 7;

		/* assign the value based on the number of bytes read */
		if(nBytesRead <= 8) {

			/* 2. Multiply the value of the unsigned number represented by the 7
			 * least significant
			 * bits of the octet by the current multiplier and add the result to
			 * the current value */
			uint64_1 += ((uint64_t) (b & 127)) << mShift1;

			/* 3. Multiply the multiplier by 128 */
			mShift1 += 7;

		} else if(nBytesRead <= 16) {

			/* 2. Multiply the value of the unsigned number represented by the 7
			 * least significant
			 * bits of the octet by the current multiplier and add the result to
			 * the current value */
			uint64_2 += ((uint64_t) (b & 127)) << mShift2;

			/* 3. Multiply the multiplier by 128 */
			mShift2 += 7;

		} else if(nBytesRead <= 24) {

			/* 2. Multiply the value of the unsigned number represented by the 7
			 * least significant
			 * bits of the octet by the current multiplier and add the result to
			 * the current value */
			uint64_3 += ((uint64_t) (b & 127)) << mShift3;

			/* 3. Multiply the multiplier by 128 */
			mShift3 += 7;

		} else if(nBytesRead <= 32) {

			/* 2. Multiply the value of the unsigned number represented by the 7
			 * least significant
			 * bits of the octet by the current multiplier and add the result to
			 * the current value */
			uint64_4 += ((uint64_t) (b & 127)) << mShift4;

			/* 3. Multiply the multiplier by 128 */
			mShift4 += 7;

		} else {

			/* error in case too large number */
			return -1; /* too large */
		}

	/* 4. If the most significant bit of the octet was 1, go back to step 1 */
	} while (errn == 0 && (b >> 7) == 1);

	/* shift actual data into array */
	if(uint64_4 != 0) {
		/* 7 octets for uint64_1 */
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 1 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 2 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 3 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 4 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 5 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 6 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 7 */

		/* 7 octets for uint64_2 */
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 1 */
		uint64_2 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 2 */
		uint64_2 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 3 */
		uint64_2 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 4 */
		uint64_2 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 5 */
		uint64_2 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 6 */
		uint64_2 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 7 */

		/* 7 octets for uint64_3 */
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_3 & 0xFF); /* 1 */
		uint64_3 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_3 & 0xFF); /* 2 */
		uint64_3 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_3 & 0xFF); /* 3 */
		uint64_3 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_3 & 0xFF); /* 4 */
		uint64_3 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_3 & 0xFF); /* 5 */
		uint64_3 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_3 & 0xFF); /* 6 */
		uint64_3 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_3 & 0xFF); /* 7 */

		/* remaining octets of uint64_4 */
		while (uint64_4 != 0 && errn == 0) {
			if(*len >= size) {

				/* report error due to out of bounds */
				return EXI_ERROR_OUT_OF_BOUNDS;
			}

			/* shift data into array */
			data[(*len)++] = uint64_4 & 0xFF;
			uint64_4 >>= 8;
		}
	} else if(uint64_3 != 0) {
		/* 7 octets for uint64_1 */
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 1 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 2 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 3 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 4 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 5 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 6 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 7 */

		/* 7 octets for uint64_2 */
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 1 */
		uint64_2 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 2 */
		uint64_2 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 3 */
		uint64_2 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 4 */
		uint64_2 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 5 */
		uint64_2 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 6 */
		uint64_2 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_2 & 0xFF); /* 7 */

		/* remaining octets of uint64_3 */
		while (uint64_3 != 0 && errn == 0) {
			if(*len >= size) {

				/* report error due to out of bounds */
				return EXI_ERROR_OUT_OF_BOUNDS;
			}

			/* shift data into array */
			data[(*len)++] = uint64_3 & 0xFF;
			uint64_3 >>= 8;
		}

	} else if(uint64_2 != 0) {
		/* 7 octets for uint64_1 */
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 1 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 2 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 3 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}


		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 4 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 5 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 6 */
		uint64_1 >>= 8;
		if(*len >= size) {

			/* report error due to out of bounds */
			return EXI_ERROR_OUT_OF_BOUNDS;
		}

		/* shift data into array */
		data[(*len)++] = (uint8_t)(uint64_1 & 0xFF); /* 7 */
		/* remaining octets of uint64_2 */
		while (uint64_2 != 0 && errn == 0) {
			if(*len >= size) {

				/* report error due to out of bounds */
				return EXI_ERROR_OUT_OF_BOUNDS;
			}

			/* shift data into array */
			data[(*len)++] = uint64_2 & 0xFF;
			uint64_2 >>= 8;
		}
	} else if(uint64_1 != 0) {
		while (uint64_1 != 0 && errn == 0) {
			if(*len >= size) {

				/* report error due to out of bounds */
				return EXI_ERROR_OUT_OF_BOUNDS;
			}

			/* shift data into array */
			data[(*len)++] = uint64_1 & 0xFF;
			uint64_1 >>= 8;
		}
	}


	/* Reverse the decoded data in the array */
	_reverseArray(data, *len);


	/* return the error code */
	return errn;
}


/************************************************************************************
* Service Name: decodeInteger
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to iv structure.
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this function calls the _decodeUnsignedIntegar function, by passing b
* 			   in sign argument indication of the sign of the data
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeInteger(bitstream_t* stream, exi_integer_t* iv) {

	/* declare variable b to put data in it */
	int b;
	/* decode boolean to know the sign of the decoded data */
	int errn = decodeBoolean(stream, &b);

	/* check if there is no errors in the decode phase */
	if (errn == 0) {

		/* call _decodeUnsignedInteger with argument b indicating the sign */
		errn = _decodeUnsignedInteger(stream, iv, b);
	}


	/* return error code */
	return errn;
}





/************************************************************************************
* Service Name: decodeInteger16
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to int16 data.
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode an arbitrary precision non negative integer using a sequence of
				 octets. The most significant bit of the last octet is set to zero to
 	 	 	 	 indicate sequence termination. Only seven bits per octet are used to
                 store the integer's value.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeInteger16(bitstream_t* stream, int16_t* int16) {

	/* declare temprory variable b to put data in it */
	int b;

	/* declare variable to put data in it */
	uint16_t uint16;

	/* decode boolean to know the sign of the data */
	int errn = decodeBoolean(stream, &b);


	/* if there is no errors in the decode phase */
	if (errn == 0) {

		/* in case negative */
		if (b) {

			errn = decodeUnsignedInteger16(stream, &uint16);

			/* For negative values, the Unsigned Integer holds the
			 * magnitude of the value minus 1 */
			*int16 = (int16_t)(-(uint16 + 1));

		/* in case positive */
		} else {
			errn = decodeUnsignedInteger16(stream, &uint16);
			*int16 = (int16_t)(uint16);
		}
	}


	/* return error code */
	return errn;
}





/************************************************************************************
* Service Name: decodeInteger32
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to int32 data.
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode an arbitrary precision non negative integer using a sequence of
				 octets. The most significant bit of the last octet is set to zero to
 	 	 	 	 indicate sequence termination. Only seven bits per octet are used to
                 store the integer's value.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeInteger32(bitstream_t* stream, int32_t* int32) {

	/* declare temprory variable b to put data in it */
	int b;

	/* declare uint32 to put data in it */
	uint32_t uint32;

	/* decode boolean to know the sign of the data */
	int errn = decodeBoolean(stream, &b);

	/* check if no errors in decode phase */
	if (errn == 0) {

		/* in case negative */
		if (b) {

			errn = decodeUnsignedInteger32(stream, &uint32);

			/* For negative values, the Unsigned Integer holds the
			 * magnitude of the value minus 1 */
			*int32 = (-(int32_t)(uint32 + 1));

		/* in case positive */
		} else {
			errn = decodeUnsignedInteger32(stream, &uint32);
			*int32 = (int32_t)(uint32);
		}
	}


	/* return error code */
	return errn;
}






/************************************************************************************
* Service Name: decodeInteger64
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to int64 data.
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode an arbitrary precision non negative integer using a sequence of
				 octets. The most significant bit of the last octet is set to zero to
 	 	 	 	 indicate sequence termination. Only seven bits per octet are used to
                 store the integer's value.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeInteger64(bitstream_t* stream, int64_t* int64) {

	/* declare temprory variable to store data in it */
	int b;

	/* declare uint64 to store data in it */
	uint64_t uint64;

	/* decode boolean to indicate the sign of the data */
	int errn = decodeBoolean(stream, &b);


	/* check if there is no errors in decode phase */
	if (errn == 0) {

		/* in case negative */
		if (b) {

			errn = decodeUnsignedInteger64(stream, &uint64);

			/* For negative values, the Unsigned Integer holds the
			 * magnitude of the value minus 1 */
			*int64 = (-(int64_t)(uint64 + 1));

		/* in case positive */
		} else {
			errn = decodeUnsignedInteger64(stream, &uint64);
			*int64 = (int64_t)(uint64);
		}
	}


	/* return error code */
	return errn;
}



/************************************************************************************
* Service Name: decodeIntegerBig
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to sign , size , pointer to array of data , pointer to lenght
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode an arbitrary precision non negative integer using a sequence of
				 octets. The most significant bit of the last octet is set to zero to
 	 	 	 	 indicate sequence termination. Only seven bits per octet are used to
                 store the integer's value.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
/* TODO : Check Validity of this function!. */
int decodeIntegerBig(bitstream_t* stream, int* negative, size_t size, uint8_t* data, size_t* len) {


	/* decode boolean to indicate the sign of the data */
	int errn = decodeBoolean(stream, negative);


	/* check if there is errors in decode phase */
	if (errn == 0) {

		/* in case negative */
		if (*negative) {
			/* For negative values, the Unsigned Integer holds the
			 * magnitude of the value minus 1 */

		/* in case positive */
		} else {
		}
		errn = decodeUnsignedIntegerBig(stream, size, data, len);
	}


	/* return error code */
	return errn;
}



/************************************************************************************
* Service Name: decodeFloat
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to exi_float structure
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: Decode a Float datatype as two consecutive Integers.
		       The first Integer represents the mantissa of the floating point
               number and the second Integer represents the base-10 exponent
               of the floating point number.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeFloat(bitstream_t* stream, exi_float_me_t* f) {

	/* decode integer64 and put data in mantissa*/
	int errn = decodeInteger64(stream, &f->mantissa);

	/* check if there is no errors in decode phase */
	if (errn == 0) {

		/* decode integer64 and put data in exponent*/
		errn = decodeInteger16(stream, &f->exponent);
	}


	/* return error code */
	return errn;
}


/************************************************************************************
* Service Name: decodeDecimal
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to exi_decimal structure
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:  Decode a decimal represented as a Boolean sign followed by two Unsigned
 	 	 	 	Integers. A sign value of zero (0) is used to represent positive Decimal
                values and a sign value of one (1) is used to represent negative Decimal
                values The first Integer represents the integral portion of the Decimal
                value. The second positive integer represents the fractional portion of
                the decimal with the digits in reverse order to preserve leading zeros.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeDecimal(bitstream_t* stream, exi_decimal_t* d) {

	/* decod boolean and put the result in exi_decimal structure */
	int errn = decodeBoolean(stream, &d->negative);

	/* check there is no errors in decode phase */
	if (errn == 0) {

		/* decode unsigned integer and put the data in the Exi_decimal Structure */
		errn = decodeUnsignedInteger(stream, &d->integral);

		/* check there is no errors in decode phase */
		if (errn == 0) {

			/* decodeUnsignedIntegar and put data in reverseFractions in Decimal Structure */
			errn = decodeUnsignedInteger(stream, &d->reverseFraction);
		}
	}


	/* return the error code */
	return errn;
}


/************************************************************************************
* Service Name: decodeStringOnly
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, lenght of string ,pointer to exi_String_t structure
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode a sequence of characters for a given length.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeStringOnly(bitstream_t* stream, size_t len, exi_string_t* s) {

	/* initialize error code to 0 */
	int errn = 0;

	/* declare the extraChar to 0 in case UNIcode */
	unsigned int extraChar = 0;

#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII

	/* declare extraChar to 1 in case ASCII */
	extraChar = 1; /* null terminator */

#endif /* STRING_REPRESENTATION_ASCII */

	/* check if lenght of string is compatible with the structure lenght */
	if ( (len + extraChar) > s->size) {

#if MEMORY_ALLOCATION == STATIC_ALLOCATION

		/* in case larger that structure lenght, report error due to out of string buffer */
		errn = EXI_ERROR_OUT_OF_STRING_BUFFER;

#endif /* STATIC_ALLOCATION */


#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION

		 /* check if size is larger than 0 in case of dynamic */
		if(s->size > 0) {
			errn = exiFreeDynamicStringMemory(s);

			/* check if there is an error */
			if(errn) {

				/* return error code */
				return errn;
			}
		}
		errn = exiAllocateDynamicStringMemory(s, (len + extraChar)); /*s->len*/
#endif /* DYNAMIC_ALLOCATION */
	}

	/* check if there is no errors */
	if(errn == 0) {

		/* call decode characters function */
		errn = decodeCharacters(stream, len, s->characters, s->size);

		/* add the lenght to the structure */
		s->len = len;
	}

	/* return the error code */
	return errn;
}





/************************************************************************************
* Service Name: decodeString
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to exi_String_t structure
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode a length prefixed sequence of characters.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeString(bitstream_t* stream, exi_string_t* s) {

	/* decode the string lenght */
	int errn = decodeUnsignedIntegerSizeT(stream, &s->len);

	/* check if there is errors in decode step */
	if (errn == 0) {

		/* decode the string */
		errn = decodeStringOnly(stream, s->len, s);
	}

	/* return the error code */
	return errn;

}





/************************************************************************************
* Service Name: decodeCharacters
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, lenght of characters, pointer to array of exi_characters_t , charSize
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode a sequence of characters according to a given length.
 	 	 	 	 Each character is represented by its UCS [ISO/IEC 10646]
   	   	   	     code point encoded as an Unsigned Integer
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeCharacters(bitstream_t* stream, size_t len, exi_string_character_t* chars, size_t charsSize) {

	/* declare variable i for illetrations */
	unsigned int i;

	/* initialize error code to 0 */
	int errn = 0;

	/* initialize extra character to 0 in case UNIcode */
	unsigned int extraChar = 0;


#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII

	/* make extraChar = 1 in case ASCII */
	extraChar = 1; /* null terminator */


#endif /* STRING_REPRESENTATION_ASCII */

 	/* check if lenght is compatible with charSize */
	if ( (len + extraChar) > charsSize) {

		/* if not, report error due to out of string buffer */
		errn = EXI_ERROR_OUT_OF_STRING_BUFFER;

		/* return error code */
		return errn;
	}

#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII

	/* declare temprory variable b to put data in it */
	uint8_t b;

 	/* illetrate on each character */
	for (i = 0; i < len && errn == 0; i++) {

		/* decode the next character */
		errn = decode(stream, &b);

		/* check if character is valid input */
		if(b < 128) {

			/* if yes, but it in characters array */
			chars[i] = (exi_string_character_t)b;
		} else {

			/* else, report error due to invalid string value */
			errn = EXI_ERROR_STRINGVALUES_CHARACTER;
		}
	}

	/* add null terminator \0 */
	chars[i] = '\0';

#endif /* STRING_REPRESENTATION_ASCII */


#if STRING_REPRESENTATION == STRING_REPRESENTATION_UCS

	/* in case Unicode, illetrate on characters */
	for (i = 0; i < len && errn == 0; i++) {

		/* decode the next character */
		errn = decodeUnsignedInteger32(stream, &chars[i]);
	}

#endif /* STRING_REPRESENTATION_UCS */



	/* return the error code */
	return errn;
}





/* TODO : check function validity */
int decodeRCSCharacters(bitstream_t* stream, size_t len, exi_string_character_t* chars, size_t charsSize, size_t rcsCodeLength, size_t rcsSize, const exi_string_character_t rcsSet[]) {
	unsigned int i;
	int errn = 0;
	uint32_t uint32;
	unsigned int extraChar = 0;
#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
	uint8_t b;
	extraChar = 1; /* null terminator */
#endif /* STRING_REPRESENTATION_ASCII */

	if ( (len + extraChar) > charsSize) {
		errn = EXI_ERROR_OUT_OF_STRING_BUFFER;
		return errn;
	}


	for (i = 0; i < len && errn == 0; i++) {
		errn = decodeNBitUnsignedInteger(stream, rcsCodeLength, &uint32);
		if(errn == 0) {
			if ( uint32 == rcsSize ) {
				/* RCS deviation */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
				errn = decode(stream, &b);
				if(b < 128) {
					chars[i] = (exi_string_character_t)b;
				} else {
					errn = EXI_ERROR_STRINGVALUES_CHARACTER;
				}
#endif /* STRING_REPRESENTATION_ASCII */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_UCS
				errn = decodeUnsignedInteger32(stream, &chars[i]);
#endif /* STRING_REPRESENTATION_UCS */

			} else {
				/* RCS match */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
				chars[i] = rcsSet[uint32];
#endif /* STRING_REPRESENTATION_ASCII */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_UCS
				chars[i] = rcsSet[uint32];
#endif /* STRING_REPRESENTATION_UCS */
			}
		}
	}

	return errn;
}





/************************************************************************************
* Service Name: decodeBinary
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to exi_bytes_t  structure
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode a binary value as a length-prefixed sequence of octets.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeBinary(bitstream_t* stream, exi_bytes_t* bytes) {

	/* decode the bytes lenght first */
	int errn = decodeUnsignedIntegerSizeT(stream, &bytes->len);

	/* check if there is no errors in decode step */
	if (errn == 0) {

		/* check if the lenght is compatible with the size */
		if (bytes->len > bytes->size) {


#if MEMORY_ALLOCATION == STATIC_ALLOCATION

			/* report error due to out of byte buffer */
			errn = EXI_ERROR_OUT_OF_BYTE_BUFFER;
#endif /* STATIC_ALLOCATION */

#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
			errn = exiFreeDynamicBinaryMemory(bytes);
			if(errn == 0) {
				errn = exiAllocateDynamicBinaryMemory(bytes, bytes->len);
			}
#endif /* DYNAMIC_ALLOCATION */
		}

		/* decode the bytes based on the lenght */
		errn = decodeBytes(stream, bytes->len, bytes->data);
	}


	/* return the error code */
	return errn;
}





/************************************************************************************
* Service Name: decodeBytes
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, lenght of bytes , pointer to array of data to put decoded data in
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   decode number of bytes based on thier lenght
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeBytes(bitstream_t* stream, size_t len, uint8_t* data) {

	/* declare variable i to be used in illetrations */
	unsigned int i;

	/* initialize error code to 0 */
	int errn = 0;

	/* declare temprory variable b to put data in it */
	uint8_t b = 0;

	/* illetrate on the bytes based on the lenght */
	for (i = 0; i < len && errn == 0; i++) {

		/* decode the next byte */
		errn = decode(stream, &b);

		/* but the byte in data array */
		data[i] = (uint8_t)b;
	}


	/* return error code */
	return errn;
}








/************************************************************************************
* Service Name: decodeDateTime
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to exi_datetime_type_t enum , pointer to exi_datetime_t structure
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   Decode Date-Time as sequence of values representing the individual
  	  	  	     components of the Date-Time.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeDateTime(bitstream_t* stream, exi_datetime_type_t type, exi_datetime_t* datetime) {

	/* initialize error code to 0 */
	int errn = 0;

	/* add the datetime type to structure type */
	datetime->type = type;


	/* initialize the datetime structure with zeros */
	datetime->year = 0;
	datetime->monthDay = 0;
	datetime->time = 0;
	datetime->presenceFractionalSecs = 0;
	datetime->fractionalSecs = 0;
	datetime->presenceTimezone = 0;
	datetime->timezone = 0;


	/* switch case on the enum type */
	switch (type) {

	/* case 1: EXI_DATETIME_GYEAR Year, [Time-Zone] */
	case EXI_DATETIME_GYEAR:

		/* decodeInteger32 to year */
		errn = decodeInteger32(stream, &datetime->year);

		/* check if there is no errors in decode step */
		if (errn == 0) {

			/* add year offset to years */
			datetime->year += DATETIME_YEAR_OFFSET;
		}
		break;


	/* Case 2 , EXI_DATETIME_GYEARMONTH Year, MonthDay, [TimeZone] pass to case 3 */
	case EXI_DATETIME_GYEARMONTH:

	/* case 3 , EXI_DATETIME_DATE */
	case EXI_DATETIME_DATE:

		/* decode the year */
		errn = decodeInteger32(stream, &datetime->year);

		/* check if there is no errors in decode step */
		if (errn == 0) {

			/* add year offset to years */
			datetime->year += DATETIME_YEAR_OFFSET;

			/* decodethe month */
			errn = decodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_MONTHDAY, &datetime->monthDay);
		}
		break;

	/* case 4 , EXI_DATETIME_DATETIME Year, MonthDay, Time, [FractionalSecs], [TimeZone] e.g. "0001-01-01T00:00:00.111+00:33" */
	case EXI_DATETIME_DATETIME:

		/* decode years */
		errn = decodeInteger32(stream, &datetime->year);

		/* check if there is no errors in decode step */
		if (errn == 0) {

			/* add year offset to years */
			datetime->year += DATETIME_YEAR_OFFSET;

			/* decode the month */
			errn = decodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_MONTHDAY, &datetime->monthDay);

			/* check if there is no errors in decode step  */
			if (errn != 0) {
				break;
			}
		}



		/* no break , continue to EXI_DATETIME_TIME case*/
	/* case 5 , EXI_DATETIME_TIME 	Time, [FractionalSecs], [TimeZone]  e.g. "12:34:56.135" */
	case EXI_DATETIME_TIME:


		/* decode time */
		errn = decodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_TIME, &datetime->time);

		/* check if there is no errors in decode step */
		if (errn == 0) {


			/* decode the presence of fractional seconds */
			errn = decodeBoolean(stream, &datetime->presenceFractionalSecs);

			/* check if there is no errors in decode step */
			if (errn == 0) {

				/* if presence of fractional seconds is true */
				if (datetime->presenceFractionalSecs) {

					/* decode the fractional seconds */
					errn = decodeUnsignedInteger32(stream, &datetime->fractionalSecs);
				}
			}
		}
		break;


	/* case 6 , EXI_ DATETIME_GMONTH MonthDay, [TimeZone]  e.g. "--12"*/
	case EXI_DATETIME_GMONTH:

	/* case 7 , EXI_DATETIME_GMONTHDAY 	MonthDay, [TimeZone]e.g. "--01-28" */
	case EXI_DATETIME_GMONTHDAY:

	/* case 8 , EXI_DATETIME_GDAY MonthDay, [TimeZone]	"---16" */
	case EXI_DATETIME_GDAY:

		/* decode monthDay */
		errn = decodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_MONTHDAY, &datetime->monthDay );

		break;

	default:

		/* report error due to unspupported date type */
		errn = EXI_UNSUPPORTED_DATETIME_TYPE;
		break;
	}


	/* check if there is no errors in decode step */
	if(errn == 0) {

		/* decode the presence of time zone */
		errn = decodeBoolean(stream, &datetime->presenceTimezone );

		/* check if no errors, and presence of time zone is true */
		if (errn == 0 && datetime->presenceTimezone) {

			/* decode the time zone */
			errn = decodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_TIMEZONE, &datetime->timezone);

			/* add offset to time zone */
			datetime->timezone -= DATETIME_TIMEZONE_OFFSET_IN_MINUTES;
		}
	}

	/* return error code */
	return errn;
}



/************************************************************************************
* Service Name: decode
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to data to write decoded data in
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:   general decode function that is used internally in many decoding functions
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decode(bitstream_t* stream, uint8_t* b) {


#if EXI_OPTION_ALIGNMENT == BIT_PACKED

	/* declare temprory variable bb to write data in it */
	uint32_t bb;

	/* decode byte, 8 bits */
	int errn =  readBits(stream, 8, &bb);

	/* check if there is no errors */
	if (errn == 0) {

		/* check if the decoded data is valid */
		if (bb > 256) {

			/* report error due to unexpected byte value */
			errn = EXI_ERROR_UNEXPECTED_BYTE_VALUE;


		} else {

			/* add decoded data to original variable */
			*b = (uint8_t)bb;
		}
	}

	return errn;
#endif /* EXI_OPTION_ALIGNMENT == BIT_PACKED */


#if EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT
	int errn = 0;
#if EXI_STREAM == BYTE_ARRAY

 	/* check if stream position is smaller than stream size */
	if ( (*stream->pos) < stream->size ) {

		/* add the decoded byte the variable and increment the position */
		*b = stream->data[(*stream->pos)++];
	} else {

		/* report error due to End of buffer */
		errn = EXI_ERROR_INPUT_STREAM_EOF;
	}
#endif /* EXI_STREAM == BYTE_ARRAY */
#if EXI_STREAM == FILE_STREAM
	*b = (uint8_t)(getc(stream->file));
	/* EOF cannot be used, 0xFF valid value */
	if ( feof(stream->file) || ferror(stream->file) ) {
		errn = EXI_ERROR_INPUT_STREAM_EOF;
	}
#endif /* EXI_STREAM == FILE_STREAM */

	return errn;
#endif /* EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT */
}





/************************************************************************************
* Service Name: decodeBoolean
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, pointer to data to write decoded data in
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:  Decode boolean data type
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeBoolean(bitstream_t* stream, int* b) {
#if EXI_OPTION_ALIGNMENT == BIT_PACKED

	/* declare temprory variable to put data in it */
	uint32_t ub;

	/* read one bit from the stream */
	int errn = readBits(stream, 1, &ub);

	/* assign the value to original data */
	*b = (ub == 0) ? 0 : 1;

	/* return error code */
	return errn;
#endif /* EXI_OPTION_ALIGNMENT == BIT_PACKED */


#if EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT

	/* declare temprory variable to put data in it */
	uint8_t bb;

 	/* decode byte */
	int errn = decode(stream, &bb);

	/* assign the decoded data to the original variable */
	*b = (bb == 0) ? 0 : 1;

	/* return error code */
	return errn;

#endif /* EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT */

}



/************************************************************************************
* Service Name: decodeNbitUnsignedInteger
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, number of bits to read , pointer to data to write decoded data in
ht* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description:  Decode boolean data type
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int decodeNBitUnsignedInteger(bitstream_t* stream, size_t nbits, uint32_t* uint32) {
#if EXI_OPTION_ALIGNMENT == BIT_PACKED

	/* initialize error code to 0 */
	int errn = 0;

	/* check if the number of bits to read = 0 */
	if (nbits == 0) {

		/* assign 0 to original variable */
		*uint32 = 0;


	} else {

		/* read the number of assigned bits from the stream */
		errn= readBits(stream, nbits, uint32);
	}

	/* return error code */
	return errn;


#endif /* EXI_OPTION_ALIGNMENT == BIT_PACKED */


#if EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT

	/* initialize bitsRead to 0 */
	size_t bitsRead = 0;

 	/* declare temprory variable b to put data in it */
	uint8_t b;

	/* initilize error code to 0 */
	int errn = 0;

	/* initilize the original data to 0 */
	*uint32 = 0;

	/* illetrate over the number of bites */
	while (errn == 0 && bitsRead < nbits) {

		/* decode byte */
		errn = decode(stream, &b);

		/* take only the needed number of bits */
		*uint32 = *uint32 + (uint32_t)(b << bitsRead);

		/* increment bits read by 8 */
		bitsRead = (bitsRead + 8);
	}

	/* return error code */
	return errn;


#endif /* EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT */
}



#endif

