#include "main.h"

extern volatile int floor_target;
extern volatile int floor_state;

// FND의 GPIO 핀 설정 (예시)
#define FND_PORT GPIOB

// 숫자 패턴 배열 (0부터 9까지)
const uint8_t fnd_patterns[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111,  // 9
	0b11111111 // allon
};
void init_fnd(void) {
    // FND 핀을 출력으로 설정
    HAL_GPIO_Init(FND_PORT, &(GPIO_InitTypeDef){FND1_Pin | FND2_Pin | FND4_Pin | FND5_Pin | FND6_Pin |
                                                FND7_Pin | FND9_Pin | FND10_Pin, GPIO_MODE_OUTPUT_PP,
                                                GPIO_NOPULL, GPIO_SPEED_FREQ_LOW});
}
// 숫자를 FND에 표시하는 함수
void display_number_on_fnd(uint8_t number) {
    // 숫자 패턴을 가져와서 FND에 출력
    uint16_t pattern = fnd_patterns[number];
    HAL_GPIO_WritePin(FND_PORT, FND1_Pin | FND2_Pin | FND4_Pin | FND5_Pin |FND6_Pin | FND7_Pin | FND9_Pin | FND10_Pin, GPIO_PIN_SET); // 모든 FND 비활성화
    HAL_GPIO_WritePin(FND_PORT, pattern, GPIO_PIN_RESET); // 해당 숫자 패턴을 FND에 출력
}

int fnd(void) {
	//초기화
    //    HAL_Init();
    //    init_fnd();


    // 숫자 표시 테스트
        display_number_on_fnd(floor_target);
//
//        HAL_GPIO_WritePin(FND_PORT, FND1_Pin | FND2_Pin | FND4_Pin | FND5_Pin |FND6_Pin | FND7_Pin | FND9_Pin | FND10_Pin, GPIO_PIN_SET);

//        if(floor_target ==floor_state)
//        {
//
//        }


}
