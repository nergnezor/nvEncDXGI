/*
 * Copyright (c) 2019, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Defs.h"
#include "DDAImpl.h"
#include "Preproc.h"
#include "NvEncoder/NvEncoderD3D11.h"
#include "Capture.h"

// void InitializeMSAA();
// void StartApps();
// Capture capture;

// int wmain(int argc, char** argv)
// {
// 	/// The app will try to capture 60 times, by default
// 	int nFrames = 60;
// 	int ret = 0;
// 	bool useNvenc = true;

// 	using clock = std::chrono::system_clock;
// 	using sec = std::chrono::duration<double>;
// 	// for milliseconds, use using ms = std::chrono::duration<double, std::milli>;

// 	const auto before = clock::now();

// 	/// Kick off the demo
// 	InitializeMSAA();
// 	ret = capture.Grab60FPS(nFrames);
// 	StartApps();
// 	const sec duration = clock::now() - before;

// 	printf("It took %.1f s (%.1f FPS)", duration.count(), nFrames / duration.count());
// 	while (true)
// 		;
// 	return ret;
// }
