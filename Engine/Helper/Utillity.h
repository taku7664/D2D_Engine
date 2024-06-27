#pragma once

struct
{
    // ����Ʈ�� �����ϸ鼭 ���� : O(n)�� �ð����⵵
    template <typename T>
    std::list<T> MergeLists(const std::list<T>& _target1, const std::list<T>& _target2)
    {
        std::vector<T> tempArr;

        tempArr.insert(tempArr.end(), _target1.cbegin(), _target1.cend());
        tempArr.insert(tempArr.end(), _target2.cbegin(), _target2.cend());

        return tempArr;
    }
    // ���͸� �����ϸ鼭 ���� : O(n)�� �ð����⵵
    template <typename T>
    std::vector<T> MergeVectors(const std::vector<T>& _target1, const std::vector<T>& _target2)
    {
        std::vector<T> tempArr;
        tempArr.reserve(_target1.size() + _target2.size()); // ���� ũ�� �̸� ���� (����ȭ)

        tempArr.insert(tempArr.end(), _target1.begin(), _target1.end());
        tempArr.insert(tempArr.end(), _target2.begin(), _target2.end());

        return tempArr;
    }

}Utillity;