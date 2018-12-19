// Copyright (c) Team CharLS. All rights reserved. See the accompanying "LICENSE.md" for licensed use.

#pragma once

#include "../src/encoder_strategy.h"


class EncoderStrategyTester : charls::EncoderStrategy
{
public:
    explicit EncoderStrategyTester(const JlsParameters& params) : EncoderStrategy(params)
    {
    }

    MSVC_WARNING_SUPPRESS(26440)
    void SetPresets(const JpegLSPresetCodingParameters&) override
    {
    }

    size_t EncodeScan(std::unique_ptr<charls::ProcessLine>, ByteStreamInfo&) override
    {
        return 0;
    }

    std::unique_ptr<charls::ProcessLine> CreateProcess(ByteStreamInfo) override
    {
        return nullptr;
    }
    MSVC_WARNING_UNSUPPRESS()

    void InitForward(ByteStreamInfo& info)
    {
        Init(info);
    }

    void AppendToBitStreamForward(int32_t value, int32_t length)
    {
        AppendToBitStream(value, length);
    }

    void FlushForward()
    {
        Flush();
    }

    std::size_t GetLengthForward() const noexcept
    {
        return GetLength();
    }

    void EndScanForward()
    {
        EndScan();
    }
};
