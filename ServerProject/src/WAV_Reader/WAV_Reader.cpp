#include "WAV_Reader.h"
inline bool isSupported(WAV_Header &header)
{
    return header.compressionCode == 1 && header.bitsPerSample == 16;
}

WAV_Reader::WAV_Reader(std::string path)
{
    if (path.empty()) return;
    this->path = path;
    readWavHeader();
}

std::string *WAV_Reader::getNextFrame(int duration)
{
    int nByteData = duration * wavData->header.byteRate / 1000;
    std::string *data = new std::string(nByteData + sizeof(WAV_Header), '\0');
    wavData->header.dataChunkSize = nByteData;
    char *p = (char *)&wavData->header;
    for (int i = 0; i < sizeof(WAV_Header); i++)
    {
        (*data)[i] = *p;
        p++;
    }

    char *tmp = new char[nByteData];
    fin.read(tmp, nByteData);

    int j = sizeof(WAV_Header);
    for (int i = 0; i < nByteData; i++)
    {
        (*data)[j++] = tmp[i];
    }
    return data;
}

WAV_Header *WAV_Reader::readWavHeader()
{
    fin.open(path);
    if (!fin.is_open()) return nullptr;

    fin.seekg(0, std::ios::beg);
    wavData = new WAV_Data;
    fin.read((char *)&wavData->header, sizeof(WAV_Header));

    if (!isSupported(wavData->header))
    {
        std::cout << "Wav file is not supported" << std::endl;
        fin.close();
        return nullptr;
    }

    fin.seekg(sizeof(WAV_Header), std::ios::beg);
    return &wavData->header;
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

bool WAV_Reader::isEOF()
{
    return fin.eof();
}

WAV_Reader::~WAV_Reader()
{
    if (wavData != nullptr) delete wavData;
    if (fin.is_open())  fin.close();
}

char* WAV_Reader::serializeWavHeader() 
{
    char *buffer = new char[45];
    char *ret = buffer;
   
    buffer = serialize(buffer, wavData->header.riffId, 4);
    buffer = serialize(buffer, wavData->header.headerChunkSize);
    buffer = serialize(buffer, wavData->header.waveId, 4);
    buffer = serialize(buffer, wavData->header.formatChunkId, 4);
    buffer = serialize(buffer, wavData->header.formatChunkSize);
    buffer = serialize(buffer, wavData->header.compressionCode);
    buffer = serialize(buffer, wavData->header.numberOfChannels);
    buffer = serialize(buffer, wavData->header.samplesRate);
    buffer = serialize(buffer, wavData->header.byteRate);
    buffer = serialize(buffer, wavData->header.blockAlign);
    buffer = serialize(buffer, wavData->header.bitsPerSample);
    buffer = serialize(buffer, wavData->header.dataChunkId, 4);
    buffer = serialize(buffer, wavData->header.dataChunkSize);
    
    return ret;
}

WAV_Header* WAV_Reader::getHeader() {
    return &wavData->header;
}
