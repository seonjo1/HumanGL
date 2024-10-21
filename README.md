# HumanGL
계층적 구조 모델의 애니메이션 구현

## HumanGL 이란?
- human model의 애니메이션 구현
- 계층적 모델링으로 human model 구현
- 변환 행렬 스택을 이용한 계층적 움직임 구현 
- Stop, Walk, Rotate, Jump 의 4가지 기본 애니메이션 구현

## human model 조작법
- Stop
  - 어떠한 키 입력도 없는 상태 (가만히 있는 상태)
  - 다른 행동 중이었을 경우 자연스럽게 정지 상태로 돌아옴
  - 정지 상태로 돌아온 경우 가만히 숨 쉬는 모션 반복 진행
- Rotate
  - 방향키 입력 방향으로 회전
- Walk
  - 방향키 입력 방향으로 이동
  - Jump 중엔 불가능
- Jump
  - space 키를 누르면 점프

## 카메라 조작법
- 마우스 조작
  - 마우스 우 클릭 Press: camera control = true (우 클릭 누른 상태로 카메라 조작)
  - 마우스 우 클릭 Release: camera control = false
  - 마우스 움직임: 카메라 회전
- 키보드 조작
  - W: 카메라 앞으로 이동
  - S: 카메라 뒤로 이동
  - A: 카메라 왼쪽으로 이동
  - D: 카메라 오른쪽으로 이동
  - Q: 카메라 위로 이동
  - E: 카메라 아래로 이동

## 설치 및 실행
### repository clone
```
git clone <repository_url>
```
### project compile
```
make
```
### program execute
```
./HumanGL
```

## 기술적 제약 사항
- 프로그래밍 언어
  - C++
- 렌더링 API
  - OpenGL
- 수학 계산 라이브러리 사용 금지
  - glmath 라이브러리 직접 구현

## 실행 결과
![HumanGL-2024-10-21-11-50-51](https://github.com/user-attachments/assets/206600b1-7cbf-4fb4-a8cd-0b5623c81002)
