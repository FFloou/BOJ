# 12015 가장 긴 증가하는 부분 수열 2
+ https://www.acmicpc.net/problem/12015
+ 이분 탐색, 가장 긴 증가하는 부분 수열: o(nlogn)
+ GoldⅡ

## 풀이
+ 전형적인 LIS 문제
+ 배열이 비어 있거나 마지막 값보다 큰 경우 배열에 해당 값을 추가
+ 그 외의 경우 lower bound의 인덱스에 해당 값을 저장
+ lower bound: 찾고자 하는 값 이상이 처음 나타나는 위치
