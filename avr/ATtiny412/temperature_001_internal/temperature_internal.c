
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>


void ADC0_init(void);
uint16_t internal_temperature(void);

void ADC0_init(void){

	//set vref to 1.1v
	VREF.CTRLA |= VREF_ADC0REFSEL_1V1_gc;

	//configure ADC to tempsense
	//ADC0.MUXPOS = ADC_MUXPOS_AIN6_gc;
	//ADC0.MUXPOS = ADC_TEMP_gm;
	ADC0.MUXPOS = ADC_MUXPOS_TEMPSENSE_gc;
	
	//clock prescaler selection
	ADC0.CTRLC |= ADC_PRESC_DIV4_gc;

	//reference selection
	ADC0.CTRLC |= ADC_REFSEL_INTREF_gc;
	
	//reduced size of sampling capacitance
	ADC0.CTRLC |= ADC_SAMPCAP_bm;

	//delay before first sample
	// 32/10^6*3.3*10^6/4 ~26.7
	// so 32 is bigger
	ADC0.CTRLD |= ADC_INITDLY_DLY32_gc; 

	//sampling lenght
	// 26.7 - 2 = 24.7 (why 2?)
	// so 25 is bigger (or maybe 27?)
	ADC0.SAMPCTRL = 27;
	
	//resolution secection
	ADC0.CTRLA |= ADC_RESSEL_10BIT_gc;
	//ADC0.CRTLA |= ADC_RESSEL_8BIT_gc;
	
	//enable ADC
	ADC0.CTRLA |= ADC_ENABLE_bm;
}

uint16_t internal_temperature(void){

		uint16_t int_temperature;
		int8_t sigrow_offset = SIGROW.TEMPSENSE1;
		uint8_t sigrow_gain = SIGROW.TEMPSENSE0;
		uint16_t adc_reading;

		ADC0.COMMAND = ADC_STCONV_bm;
		while (!(ADC0.INTFLAGS & ADC_RESRDY_bm)){
			;
		}
		ADC0.INTFLAGS = ADC_RESRDY_bm;
		//attiny_temperature = ADC0.RES;
		adc_reading = ADC0.RES;
		uint32_t temp = adc_reading - sigrow_offset;
		temp *= sigrow_gain;
		temp += 0x80;
		temp >>= 8;
		int_temperature = temp;
		//change from Kelvin to Celsius
		int_temperature -= 273;
		return (int_temperature);
}
