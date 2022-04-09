# 4386 별자리 만들기
+ https://www.acmicpc.net/problem/4386
+ 그래프 이론, 최소 스패닝 트리
+ GoldIV

## 풀이
+ 크루스칼 알고리즘을 사용하여 MST를 만든다.
+ 두 점을 선택하는 모든 경우의 점과 길이를 priority_queue에 삽입한다.
+ union-find 알고리즘으로 MST를 만들어 나간다.
+ 소수점 둘째짜리까지 표현하므로 다음과 같은 코드를 사용한다.
  ```
    cout.fixed;
    cout.precision(2);
  ```
