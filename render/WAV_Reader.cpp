#include "WAV_Reader.h"
inline bool isSupported(WavHeader &header)
{
    return header.compressionCode == 1 && header.bitsPerSample == 16;
}

WAV_Reader::WAV_Reader(std::string path)
{
    if (path.empty()) return;
    readWavFile(path);
}

WavData* WAV_Reader::readWavFile(std::string path) 
{
    if (path.empty()) return nullptr;
    this->path = path;

    fin.open(path, std::ios::binary);
    if(fin.is_open() == false) return nullptr;

    fin.seekg(0, std::ios::beg);
    wavData = new WavData;
    fin.read((char *)&wavData->header, sizeof(WavHeader));

    if (!isSupported(wavData->header))
    {
        std::cout << "Wav file is not supported" << std::endl;
        fin.close();
        return nullptr;
    }

    fin.seekg(sizeof(WavHeader), std::ios::beg);
    wavData->dataChunk.resize(wavData->header.dataChunkSize);
    fin.read((char *)wavData->dataChunk.data(), wavData->header.dataChunkSize);
    duration = wavData->header.dataChunkSize / wavData->header.byteRate;
    return wavData;
}

void WAV_Reader::showHeaderInfo()
{
    if (wavData == nullptr) return;

    std::cout << "Header chunk ID: " << std::string(wavData->header.riffId, 4) << std::endl;
    std::cout << "Header chunk size: " << wavData->header.headerChunkSize << std::endl;
    std::cout << "Wave ID: " << std::string(wavData->header.waveId, 4) << std::endl;

    std::cout << "Format chunk ID: " << std::string(wavData->header.formatChunkId, 4) << std::endl;
    std::cout << "Format chunk size: " << wavData->header.formatChunkSize << std::endl;
    std::cout << "Compression code: " << wavData->header.compressionCode << std::endl;
    std::cout << "Number of channels: " << wavData->header.numberOfChannels << std::endl;
    std::cout << "Sample rate: " << wavData->header.samplesRate << std::endl;
    std::cout << "Byte rate: " << wavData->header.byteRate << std::endl;
    std::cout << "Block align: " << wavData->header.blockAlign << std::endl;
    std::cout << "Bits per sample: " << wavData->header.bitsPerSample << std::endl;

    std::cout << "Data chunk ID: " << std::string(wavData->header.dataChunkId, 4) << std::endl;
    std::cout << "Data chunk size: " << (wavData->header.dataChunkSize) << std::endl;
}

WAV_Reader::~WAV_Reader()
{
    if(wavData != nullptr) delete wavData;
    if(splitedData != nullptr) delete splitedData;
    if(fin.is_open()) fin.close();
}

// std::vector<char> *WAV_Reader::getWavData() const {
//     return &wavData->dataChunk;
// }

std::string WAV_Reader::getPath() const {
     return path; 
}

std::vector<WavData>* WAV_Reader::splitWavData(int secPerSegment)
{
    if (wavData == nullptr) return nullptr;
    int nSegment = (duration-1) / secPerSegment + 1;
    splitedData = new std::vector<WavData>(nSegment, WavData{});
    
    // handle header of wav
    int totalSecond = duration;
    int cntSecond = secPerSegment;
    int cntByte = 0;
    
    for (size_t i = 0; i < splitedData->size(); ++i)
    {
        if (totalSecond < secPerSegment) cntSecond = totalSecond;

        int chunkSize = wavData->header.byteRate * cntSecond;
        (*splitedData)[i].dataChunk.resize(chunkSize);
        (*splitedData)[i].header = wavData->header;
        (*splitedData)[i].header.dataChunkSize = chunkSize;
        cntByte += chunkSize;
        totalSecond -= secPerSegment;
    }
    
    // handle body of wav
    for (size_t i = 0; i < cntByte; ++i)
    {
        int bytePerSec = wavData->header.byteRate * secPerSegment;
        (*splitedData)[i / bytePerSec].dataChunk[i % bytePerSec] = wavData->dataChunk[i];
    }

    // store splited wav files
    for (size_t i = 0; i < splitedData->size(); ++i)
    {
        std::ofstream fout(std::string("./WAV/wav_") + std::to_string(i) + std::string(".wav"), std::ios::binary);
        fout.write((char *)(&splitedData[0][i].header), sizeof(WavHeader));
        fout.write(splitedData[0][i].dataChunk.data(), splitedData[0][i].dataChunk.size());
        fout.close();
    }

    return splitedData;
}
