#include "PlayerWork.hpp"
#include "Dpr/Nx/SaveSystem.hpp"

#include <cstdlib>
#include <cstdio>
#include "logger.hpp"
#include "Save.hpp"
#include "util.hpp"
#include "System/String.hpp"
#include "il2cpp.hpp"
#include "nn/fs.h"
#include "Dpr/Nx/SaveSystem.hpp"

bool PlayerWork_CustomSaveAsyncOperation_Reroute(PlayerWork *this_, MethodInfo *method)
{
  this_->CustomSaveOperation((MethodInfo *) nullptr);
  return true;
}

void PlayerWork_CustomSaveAsyncOperation_NewHook(PlayerWork *this_, System_Byte_array ** ptr_buf, MethodInfo * method)
{
  socket_log("PlayerWork_CustomSaveAsyncOperation_NewHook\n");
  socket_log_fmt("this_: %08X\n", this_);
  DPData::ZUKAN_WORK_o zukanWork = PlayerWork::get_zukan(nullptr, nullptr);
  System_Byte_array *data = * ptr_buf;
  uint8_t * buf = (uint8_t *) &data->m_Items;
  void * ptr = PlayerWork::get_tr_battleData()->m_Items;
  socket_log_fmt("ptr: %08X\n", ptr);
  uint32_t version = 0xFFFF0000 | 0x0100 | 0x34; // Rev 1 Lumi Save
  memcpy(&buf[0], &version, sizeof(uint32_t));
  memcpy(&buf[0x7D3E0], ptr, 0x586); // 0x1618
  // Pokedex Save Data
  memcpy(&buf[0x7A328], &zukanWork.fields.get_status->m_Items, 0x1ed * sizeof(int32_t));
  memcpy(&buf[0x7aadc], &zukanWork.fields.male_color_flag->m_Items, 0x1ed); 
  memcpy(&buf[0x7acc9], &zukanWork.fields.female_color_flag->m_Items, 0x1ed);
  memcpy(&buf[0x7aeb6], &zukanWork.fields.male_flag->m_Items, 0x1ed); 
  memcpy(&buf[0x7b0a3], &zukanWork.fields.female_flag->m_Items, 0x1ed);
  return;
}

bool Dpr_NX_SaveSystem_Save(System_Byte_array *data, bool writeMain, bool writeBackup, MethodInfo * method)
{
  bool success = true;
  nn::fs::FileHandle fileHandle{};
  
  //system_load_typeinfo((void *)0x757e);
  //il2cpp_runtime_class_init(Dpr::Nx::SaveSystem_TypeInfo);

  //socket_log_fmt("Before Mount\n");

  //Dpr::Nx::SaveSystem::MountSaveData((MethodInfo *) nullptr);

  //socket_log_fmt("After Mount\n");

  socket_log_fmt("Skipped mount!!\n");
  socket_log_fmt("data: %08X, writeMain: %d, writeBackup: %d\n", data, writeMain, writeBackup);

  if (writeMain) {
    bool createdFiles = true;

    socket_log_fmt("Before Create SaveData\n");

    nn::fs::DeleteFile("SaveData:/SaveData.bin");
    createdFiles &= nn::fs::CreateFile("SaveData:/SaveData.bin",(s64)*(&data->max_length)).isSuccess();

    socket_log_fmt("After Create SaveData\n");
    socket_log_fmt("Before Create Luminescent_Backup\n");

    // Lumi Backup
    nn::fs::DeleteFile("SaveData:/Luminescent_Backup.bin");
    createdFiles &= nn::fs::CreateFile("SaveData:/Luminescent_Backup.bin",(s64)*(&data->max_length)).isSuccess();

    socket_log_fmt("After Create Luminescent_Backup\n");

    if (!createdFiles) return false;

    socket_log_fmt("Before Save SaveData\n");

    nn::fs::OpenFile(&fileHandle,"SaveData:/SaveData.bin",2);
    success &= nn::fs::WriteFile(fileHandle,0,data->m_Items,(s64)*(&data->max_length),nn::fs::WriteOption(1)).isSuccess();
    nn::fs::CloseFile(fileHandle);

    socket_log_fmt("After Save SaveData\n");
    socket_log_fmt("Before Save Luminescent_Backup\n");

    // Lumi Backup
    nn::fs::OpenFile(&fileHandle,"SaveData:/Luminescent_Backup.bin",2);
    success &= nn::fs::WriteFile(fileHandle,0,data->m_Items,(s64)*(&data->max_length),nn::fs::WriteOption(1)).isSuccess();
    nn::fs::CloseFile(fileHandle);

    socket_log_fmt("After Save Luminescent_Backup\n");
  }

  if (writeBackup) {

    socket_log_fmt("Before Create Backup\n");

    nn::fs::DeleteFile("SaveData:/Backup.bin");
    if (nn::fs::CreateFile("SaveData:/Backup.bin", (s64)*(&data->max_length)).isFailure()) return false;

    socket_log_fmt("After Create Backup\n");
    socket_log_fmt("Before Save Backup\n");

    nn::fs::OpenFile(&fileHandle,"SaveData:/Backup.bin",2);
    success &= nn::fs::WriteFile(fileHandle,0,data->m_Items,(s64)*(&data->max_length),nn::fs::WriteOption(1)).isSuccess();
    nn::fs::CloseFile(fileHandle);

    socket_log_fmt("After Save Backup\n");
  }

  return success;
}
