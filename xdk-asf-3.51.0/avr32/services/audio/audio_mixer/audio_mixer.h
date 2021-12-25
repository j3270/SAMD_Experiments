/*****************************************************************************
 *
 * \file
 *
 * \brief Audio mixer.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 ******************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#ifndef _AUDIO_MIXER_H_
#define _AUDIO_MIXER_H_

#include <stddef.h>

#include "compiler.h"

#if defined(USE_AUDIO_PLAYER_BUFFERIZATION) && \
    USE_AUDIO_PLAYER_BUFFERIZATION == true
  #include "buff_player.h"
#endif

#if defined(USE_AUDIO_PLAYER_BUFFERIZATION) && \
    USE_AUDIO_PLAYER_BUFFERIZATION == true
  #define audio_mixer_create_buffers(...)       buff_player_create(__VA_ARGS__)
  #define audio_mixer_close(...)                buff_player_close(__VA_ARGS__)
  #define audio_mixer_get_buffer(...)           buff_player_malloc(__VA_ARGS__)
  #define audio_mixer_dacs_setup(...)           buff_player_dacs_setup(__VA_ARGS__)
  #define audio_mixer_dacs_output(...)          buff_player_dacs_output(__VA_ARGS__)
  #define audio_mixer_dacs_flush(...)           buff_player_dacs_flush(__VA_ARGS__)
  #define audio_mixer_mute_audio(...)           buff_player_mute_audio(__VA_ARGS__)
#else
  #define audio_mixer_create_buffers(...)       audio_mixer_create_buffers_direct(__VA_ARGS__)
  #define audio_mixer_close(...)                audio_mixer_close_direct(__VA_ARGS__)
  #define audio_mixer_get_buffer(...)           audio_mixer_get_buffer_direct(__VA_ARGS__)
  #define audio_mixer_dacs_setup(...)           audio_mixer_dacs_setup_direct(__VA_ARGS__)
  #define audio_mixer_dacs_output(...)          audio_mixer_dacs_output_direct(__VA_ARGS__)
  #define audio_mixer_dacs_flush(...)           audio_mixer_dacs_flush_direct(__VA_ARGS__)
  #define audio_mixer_mute_audio(...)           audio_mixer_mute_audio_direct(__VA_ARGS__)
#endif

#define audio_mixer_enable_dacs(...)            audio_mixer_enable_dacs_direct(__VA_ARGS__)
#define audio_mixer_dacs_start(...)             audio_mixer_dacs_start_direct(__VA_ARGS__)
#define audio_mixer_dacs_increase_volume(...)   audio_mixer_dacs_increase_volume_direct(__VA_ARGS__)
#define audio_mixer_dacs_decrease_volume(...)   audio_mixer_dacs_decrease_volume_direct(__VA_ARGS__)
#define audio_mixer_dacs_get_volume(...)        audio_mixer_dacs_get_volume_direct(__VA_ARGS__)
#define audio_mixer_dacs_set_volume(...)        audio_mixer_dacs_set_volume_direct(__VA_ARGS__)
#define audio_mixer_dacs_is_volume_muted(...)   audio_mixer_dacs_is_volume_muted_direct(__VA_ARGS__)
#define audio_mixer_dacs_stop(...)              audio_mixer_dacs_stop_direct(__VA_ARGS__)
#define audio_mixer_disable_dacs(...)           audio_mixer_disable_dacs_direct(__VA_ARGS__)
#define audio_mixer_dacs_input(...)             audio_mixer_dacs_input_direct(__VA_ARGS__)



/*! \brief Enables the handling of the specified DACs by the audio mixer.
 */
extern void audio_mixer_enable_dacs_direct(uint32_t dacs_mask);

/*! \brief Creates DAC buffers.
 */
extern bool audio_mixer_create_buffers_direct(uint8_t nb_buffers,
                                              size_t buffer_size);

/*! \brief Close the audio_mixer.
 */
extern void audio_mixer_close_direct(void);

/*! \brief This functions returns a NULL pointer when no buffer are free,
 *         else returns a free temporary buffer.
 */
extern void *audio_mixer_get_buffer_direct(size_t size);

/*! \brief Starts the DACs.
 */
extern void audio_mixer_dacs_start_direct(uint32_t sample_rate_hz,
                                          uint8_t num_channels,
                                          uint8_t bits_per_sample,
                                          bool swap_channels);

/*! \brief Sets the DACs up with new settings.
 *
 * \note The DACs must have been started beforehand.
 */
extern void audio_mixer_dacs_setup_direct(uint32_t sample_rate_hz,
                                          uint8_t num_channels,
                                          uint8_t bits_per_sample,
                                          bool swap_channels);

/*! \brief Outputs a sample buffer to the DACs.
 *
 * \note The DACs must have been started beforehand.
 */
extern bool audio_mixer_dacs_output_direct(void *sample_buffer,
                                           size_t sample_length);

/*! \brief Increases the output volume of the DACs.
 *
 * \note The DACs must have been started beforehand.
 */
extern void audio_mixer_dacs_increase_volume_direct(void);

/*! \brief Decreases the output volume of the DACs.
 *
 * \note The DACs must have been started beforehand.
 */
extern void audio_mixer_dacs_decrease_volume_direct(void);

/*! \brief Get the average volume of the DACs.\n
 *         The value returned is in the range 0; 255 where
 *         255 corresponds to the highest volume.
 *
 * \note The DACs must have been started beforehand.
 */
extern uint8_t audio_mixer_dacs_get_volume_direct(void);

/*! \brief set the average volume of the DACs.\n
 *
 * \note The DACs must have been started beforehand.
 */
extern void audio_mixer_dacs_set_volume_direct(uint8_t volume);

/*! \brief Checks if the volume is muted or un-muted.\n
 *
 * \note The DACs must have been started beforehand.
 */
extern bool audio_mixer_dacs_is_volume_muted_direct(void);

/*! \brief Flushes the sample buffer being output to the DACs.
 * \param force Force flushing means do not wait until all samples have been
 *              played before flushing the DAC.
 */
extern void audio_mixer_dacs_flush_direct(bool force);

/*! \brief Stops the DACs.
 */
extern void audio_mixer_dacs_stop_direct(void);

/*! \brief Disables the handling of the specified DACs by the audio mixer.
 */
extern void audio_mixer_disable_dacs_direct(uint32_t dacs_mask);

/*! \brief Mute Audio if True
 * \param mute Set to true to mute the audio stream.\n
 *             Set to false otherwise.
 */
extern void audio_mixer_mute_audio_direct(bool mute);

/*! \brief Inputs a sample buffer from the ADCs.
 *
 * \note The ADCs must have been started beforehand.
 */
extern bool audio_mixer_dacs_input_direct(void *sample_buffer,
                                           size_t sample_length);

#endif  // _AUDIO_MIXER_H_
