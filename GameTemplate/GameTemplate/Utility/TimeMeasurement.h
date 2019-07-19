#pragma once

#include <chrono>
#include <unordered_map>
#include <Windows.h>
#include <functional>
#include "Utility/Singleton.h"

namespace Utility {

/**
* @class TimeMeasurement
* @brief ���Ԍv��
*/
class TimeMeasurement : public Singleton<TimeMeasurement> {
    /**
    * @enum UnitType
    * @brief ���Ԃ̒P��
    */
    enum class UnitType {
        MilliSeconds,
        MicroSeconds,
    };

private:
    using Time = std::chrono::system_clock::time_point;
    //�����Ɍv�����ԊԊu�A�߂�l�ɂ��̊Ԋu�ɕϊ��������Ԃ�Ԃ��֐�
    using GetTimeFunc = std::function<
        long long(std::chrono::duration<long long, std::ratio_multiply<std::hecto, std::nano>>)
    >;
public:
    /**
    * @brief �R���X�g���N�^
    */
    TimeMeasurement();
    /**
    * @brief �f�X�g���N�^
    */
    ~TimeMeasurement();
    /**
    * @brief �v���J�n
    */
    void start();
    /**
    * @brief �v���I��
    * @param �v���������Ԃ̒P��
    * @return start����end�܂ł̌o�ߎ���
    */
    long long end(UnitType type = UnitType::MilliSeconds);
private:
    Time mStartTime; //!< �J�n����
    std::unordered_map<UnitType, GetTimeFunc> mGetTimeFuncs;
};

} //Utility 