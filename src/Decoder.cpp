#include "Decoder.h"
#include <vector>
#include <cuda.h>
#include "NvDecoder/NvDecoder.h"
#include "Utils/NvCodecUtils.h"
#include "Utils/FFmpegDemuxer.h"
#include "AppDecode/Common/AppDecUtils.h"

simplelogger::Logger *logger = simplelogger::LoggerFactory::CreateConsoleLogger();

int Decoder::Decode(char szInFilePath[256])
{
    char szOutFilePath[256] = "out.yuv";
    int iGpu = 0;
    bool bVerbose = false;
    try
    {
        //ParseCommandLine(argc, argv, szInFilePath, szOutFilePath, iGpu, &bVerbose);
        //CheckInputFile(szInFilePath);

        ck(cuInit(0));
        int nGpu = 0;
        ck(cuDeviceGetCount(&nGpu));
        if (iGpu < 0 || iGpu >= nGpu)
        {
            std::ostringstream err;
            err << "GPU ordinal out of range. Should be within [" << 0 << ", " << nGpu - 1 << "]" << std::endl;
            throw std::invalid_argument(err.str());
        }

        CUcontext cuContext = NULL;
        createCudaContext(&cuContext, iGpu, 0);

        FFmpegDemuxer demuxer(szInFilePath);
        // Here set bLowLatency=true in the constructor.
        // Please don't use this flag except for low latency, it is harder to get 100% utilization of
        // hardware decoder with this flag set.
        NvDecoder dec(cuContext, false, FFmpeg2NvCodecId(demuxer.GetVideoCodec()), NULL, true);

        int nFrame = 0;
        uint8_t *pVideo = NULL;
        int nVideoBytes = 0;
        std::ofstream fpOut(szOutFilePath, std::ios::out | std::ios::binary);
        if (!fpOut)
        {
            std::ostringstream err;
            err << "Unable to open output file: " << szOutFilePath << std::endl;
            throw std::invalid_argument(err.str());
        }

        int n = 0;
        bool bOneInOneOut = true;
        uint8_t **ppFrame;
        int64_t *pTimestamp;
        int nFrameReturned = 0;
        do
        {
            demuxer.Demux(&pVideo, &nVideoBytes);
            // Set flag CUVID_PKT_ENDOFPICTURE to signal that a complete packet has been sent to decode
            dec.Decode(pVideo, nVideoBytes, &ppFrame, &nFrameReturned, CUVID_PKT_ENDOFPICTURE, &pTimestamp, n++);
            if (!nFrame && nFrameReturned)
                LOG(INFO) << dec.GetVideoInfo();

            nFrame += nFrameReturned;
            // For a stream without B-frames, "one in and one out" is expected, and nFrameReturned should be always 1 for each input packet
            if (bVerbose)
            {
                std::cout << "Decode: nVideoBytes=" << nVideoBytes << ", nFrameReturned=" << nFrameReturned << ", total=" << nFrame << std::endl;
            }
            if (nVideoBytes && nFrameReturned != 1)
            {
                bOneInOneOut = false;
            }
            for (int i = 0; i < nFrameReturned; i++)
            {
                if (bVerbose)
                {
                    std::cout << "Timestamp: " << pTimestamp[i] << std::endl;
                }
                fpOut.write(reinterpret_cast<char *>(ppFrame[i]), dec.GetFrameSize());
            }
        } while (nVideoBytes);

        fpOut.close();
        std::cout << "One packet in and one frame out: " << (bOneInOneOut ? "true" : "false") << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what();
        exit(1);
    }
    return 0;
}
