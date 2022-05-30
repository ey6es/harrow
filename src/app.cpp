#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>

// see https://docs.fileformat.com/audio/wav/
struct wave_header {
  char magic[4] = {'R', 'I', 'F', 'F'};
  uint32_t file_size;
  char file_type[4] = {'W', 'A', 'V', 'E'};
  char format_chunk_marker[4] = {'f', 'm', 't', ' '};
  uint32_t format_data_length = 16;
  uint16_t format_type = 1;
  uint16_t channel_count;
  uint32_t sample_rate = 44100;
  uint32_t data_rate;
  uint16_t bytes_per_frame;
  uint16_t bits_per_sample = 16;
  char data_chunk_marker[4] = {'d', 'a', 't', 'a'};
  uint32_t data_chunk_length;

  wave_header (bool stereo, int frame_count) :
    channel_count(stereo ? 2 : 1),
    data_rate(44100 * 2 * channel_count),
    bytes_per_frame(2 * channel_count),
    data_chunk_length(bytes_per_frame * frame_count)
  {
    file_size = data_chunk_length + sizeof(wave_header) - sizeof(magic) - sizeof(file_size);
  }
};

int main () {
  const int frame_count = 44100;
  wave_header header(false, frame_count);
  std::cout.write(reinterpret_cast<char*>(&header), sizeof(header));

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);

  std::uniform_int_distribution<int16_t> distribution(-1024,1024);

  for (int i = 0; i < 44100; i++) {
    int16_t sample = distribution(generator);
    std::cout.write(reinterpret_cast<char*>(&sample), sizeof(sample));
  }
}
