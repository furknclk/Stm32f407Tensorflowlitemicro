#include "stm32f4xx.h"                  // Device header
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/testing/micro_test.h"
#include "tensorflow/lite/version.h"
#include "sine_wave.h"
#include <string.h>
#define PI 3.141592654
uint32_t delays;
void delay(uint32_t i){
uint32_t tick_count=16800;
	while(tick_count){
		delays=i;
		while(delays){ delays--;}
		tick_count--;
		
	}

	
}
const int tensor_arena_size = 4 * 1024;
__attribute__((aligned(16))) uint8_t tensor_arena[tensor_arena_size];

int main(){
	SystemCoreClockUpdate();
	/** PWM için timer ve GPIO ayarlamalari yapiliyor.**/
	RCC->APB1ENR|=0x04;
	RCC->AHB1ENR|=0x08;
	GPIOD->MODER|=0xAA000000;
	GPIOD->AFR[1]=0x22220000;
	TIM4->CCMR1|=0x60;
	TIM4->CCMR1|=0x6000;
	TIM4->CCMR2|=0x60;
	TIM4->CCMR2|=0x6000;
	TIM4->CCER|=0x1111;
	TIM4->PSC=(84-1);
	TIM4->ARR=100;

	tflite::MicroErrorReporter  err;
	tflite::ErrorReporter* error_reporter= &err;
	
	tflite::AllOpsResolver resolver;
	const tflite::Model* model=::tflite::GetModel(sine_wave);
	
	if (model->version() != TFLITE_SCHEMA_VERSION) {//Versiyon karsilastirmasi yapiliyor
	error_reporter->Report(" VERSIYON HATASI ! Model versiyonu %d,tflite_schema_version %d",model->version(), TFLITE_SCHEMA_VERSION);
	return 1;
}
	tflite::MicroInterpreter interpreter(model, resolver, tensor_arena,tensor_arena_size, error_reporter);//Interpreter kuruluyor

	interpreter.AllocateTensors();
	TfLiteTensor* input = interpreter.input(0);
	float i=0.0f;
	while(1){
	input->data.f[0] = i;
	TfLiteStatus invoke_status = interpreter.Invoke();
	if (invoke_status != kTfLiteOk) {
	error_reporter->Report("Model kosturulamadi\n");
	}
	TfLiteTensor* output = interpreter.output(0);
	float value =output->data.f[0];
	
	error_reporter->Report("sin=%f alpha=%f",value,i);//Radyan cinsinden açi degerinin sinüs karsiligi yazdiriliyor
	TIM4->CCR1=(100-100*value)/2;
	TIM4->CR1|=0x01;
  i+=0.01f;
	if(i>2*PI) i=0.0f;
	delay(1);//bir miktar bekleme süresi olusturuldu
}
}