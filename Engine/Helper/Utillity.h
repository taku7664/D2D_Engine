#pragma once

struct
{
    // 리스트를 복사하면서 병합 : O(n)의 시간복잡도
    template <typename T>
    std::list<T> MergeLists(const std::list<T>& _target1, const std::list<T>& _target2)
    {
        std::vector<T> tempArr;

        tempArr.insert(tempArr.end(), _target1.cbegin(), _target1.cend());
        tempArr.insert(tempArr.end(), _target2.cbegin(), _target2.cend());

        return tempArr;
    }
    // 벡터를 복사하면서 병합 : O(n)의 시간복잡도
    template <typename T>
    std::vector<T> MergeVectors(const std::vector<T>& _target1, const std::vector<T>& _target2)
    {
        std::vector<T> tempArr;
        tempArr.reserve(_target1.size() + _target2.size()); // 벡터 크기 미리 예약 (최적화)

        tempArr.insert(tempArr.end(), _target1.begin(), _target1.end());
        tempArr.insert(tempArr.end(), _target2.begin(), _target2.end());

        return tempArr;
    }

}Utillity;