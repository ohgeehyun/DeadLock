#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

/*
    AccoutManager의 mutex lock과 UserMnager의 mutex lock 2개의 서로 다른 뮤텍스 락을 걸게되는 구조
    실제로 서로 다른 뮤텍스락이 서로 참조를하게되는 바람에 데드락발생하는경우가 있다고한다.
    교착상태에 빠저버린것이다. 자원이2개있어야 일이 마무리되는데 자원을 하나씩 가지고 놔주질않아.
    딱 운영체제 책에서 본 그대로다.
    다수의 자원을 순서대로 가지거나 한번에 2개다 가질수있는 상황을 만들지않으면 데드락을 방지할수있다. 
    ex) lock_guard<mutex> guard(_mutex);의 위치를 바꿔도 해결된다는 뜻. 현재 프로젝트에선 일부로 막아놓았다. 풀어보자
    그외에도 데드락 방지 회피법은 다양하게있으니 알아보자.
    책에서는 보지 못한 방법으로는 디버그시 그래프알고리즘을 이용해 싸이클이 발생하는지 확인하는 스레드 매니저를만들어 추적하는 방법도있다고 한다.
 */

void Func1() {
    for (int32 i = 0; i < 10000; i++) {
        UserManager::Instance()->ProcessSave();
    }
}
void Func2() {
    for (int32 i = 0; i < 10000; i++) {
        AccountManager::Instance()->ProcessLogin();
    }

}


int main()
{
    thread t1(Func1);
    thread t2(Func2);

    t1.join();
    t2.join();

    std::cout << "jobs done"<<"\n";

    /*참고
    mutex m1;
    mutex m2;
    lock(m1, m2);//알아서 순서에 따른 내부적으로 데드락 방지 
    */
}



