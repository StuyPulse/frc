#include "Compressor.h"
#include "CCompressor.h"
static Compressor *compressor = NULL;


void CreateCompressor(UINT32 pressureSwitchChannel, UINT32 relayChannel)
{
	if (compressor == NULL)
	{
		compressor = new Compressor(pressureSwitchChannel, relayChannel);
		return;
	}
	wpi_fatal(CompressorAlreadyDefined);
}

void CreateCompressor(UINT32 pressureSwitchSlot, UINT32 pressureSwitchChannel,
						UINT32 relaySlot, UINT32 relayChannel)
{
	if (compressor == NULL)
	{
		compressor = new Compressor(pressureSwitchSlot, pressureSwitchChannel,
									relaySlot, relayChannel);
		return;
	}
	wpi_fatal(CompressorAlreadyDefined);
}

void StartCompressor(void)
{
	if (compressor == NULL)
	{
		wpi_fatal(CompressorUndefined);
		return;
	}
	compressor->Start();
}

void StopCompressor(void)
{
	if (compressor == NULL)
	{
		wpi_fatal(CompressorUndefined);
		return;
	}
	compressor->Stop();
}

bool CompressorEnabled(void)
{
	if (compressor == NULL)
	{
		wpi_fatal(CompressorUndefined);
		return false;
	}
	return compressor->Enabled();
}

