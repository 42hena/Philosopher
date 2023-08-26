# Dining philosophers problem
/Users/hena/42Seoul/img/Dining.png

## Deadlock 처리 방법 - (3 ways)
1. Deadlock prevention or avoidance:

### Prevention: 시스템이 교착 상태에 빠지지 않도록 하는 것
- 비용이 많이 들기 때문에 교착 상태에 빠지지 않게 하는 것이 최우선인 경우 사용.
- 교착 상태의 필수 조건 중 하나를 무효화하여 예방.
- Solve hold and Wait(점유 및 대기)
- Eliminate mutual exclusion(상호 배제)
- Allow preemption(선점)
- Circular wait Solution(환형 대기)

### Avoidance:
Avoidance is kind of futuristic. By using the strategy of “Avoidance”, we have to make an assumption. We need to ensure that all information about resources that the process will need is known to us before the execution of the process. We use Banker’s algorithm (Which is in turn a gift from Dijkstra) to avoid deadlock. 

- 비용이 많이 들음.
------------------------

2. Deadlock detection and recovery: 

첫 번째, 프로세스 상태를 검사하고 시스템에 교착 상태가 있는지 여부를 확인.
두 번째, 교착 상태가 발견 시 복구 알고리즘을 적용.

교착 상태 감지 및 복구에서는 데이터의 정확성을 확보하지만 성능이 저하.

Recovery from Deadlock (회복 기법)

1. Manual Intervention: 수동 개입
- 운영자에게 알리고 수동으로 상황을 처리.
- 사람의 판단과 의사 결정이 필요.
- 시간이 오래 걸릴 수 있으므로 대규모 시스템에서 불가능.

2. Automatic Recovery: 자동 복구
- 교착 상태에서 자동으로 복구할 수 있도록 하는 것.

#### Process Termination:
##### 1. 교착 상태에 있는 모든 프로세스 종료.
- 상태 주기를 끊을 수 있지만 상당한 비용이 발생.
- 이미 실행된 부분도 다시 연산해야함.

##### 2. Abort one process at a time:
- 교착 주기가 제거될 때까지 한 번에 한 프로세스씩 선택적으로 중단하는 방식.
- 교착 상태의 프로세스가 있는지 확인하기 위해 교착 상태 감지 알고리즘을 호출해야 하므로 오버헤드가 발생.

종료 순서를 선택하는 요소들
- 프로세스의 우선순위
– 완료 시간 및 지금까지의 진행 상황
– 프로세스에 사용된 리소스
– 프로세스를 완료하는 데 필요한 리소스
– 종료할 프로세스 수
– 프로세스의 유형(대화형 또는 일괄 처리)

### Resource Preemption:
1. 희생자 선택
- 선택 순서는 전체 복구 비용을 최소화 하는 것.

2. 롤백
- 프로세스를 안전한 상태로 롤백하고 다시 시작하는 것
- 안전한 상태를 판단하는 것이 어려울 수 있으므로 프로세스를 중단하고 처음부터 다시 시작하는 전체 롤백을 사용하기도 합니다.

3. 자원 고갈 방지
- 리소스 고갈을 방지하려면 항상 동일한 프로세스가 희생 대상으로 선택되지 않도록 하는 것이 중요. 
- 비용 요소만을 기준으로 피해 프로세스를 선택하면 한 프로세스가 반복적으로 리소스를 잃고 지정된 작업을 완료하지 못할 수 있습니다. 
- 비용 요소에 롤백 횟수를 포함하여 프로세스가 피해자로 선택될 수 있는 횟수를 제한하는 것이 좋습니다.


### Deadlock ignorance : 교착 상태가 발생하도록 냅두고, 발생 시 시스템 재부팅
- 1번과 2번보다 성능은 우수하지만 데이터의 정확성은 떨어짐.