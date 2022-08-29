/*
 * MIT License
 * 
 * Copyright (c) 2022 Yonder
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "gecko.h"
#include "csprintf_s.h"

#define TOSTR(s)  #s

typedef enum __makecodeStatus {
    MCS_SUCCESS,
    MCS_ERROR,
    MCS_INVLDARG
} makecodeStatus;

typedef enum __Code {
    CDE_INVALID = -1,
    CDE_RESTOREBEAMFX,
    CDE_DISABLEBLOOM,
    CDE_RESTOREDASHING,
    CDE_ENABLESKIPCUTSCENE,
    CDE_FRIENDVOUCHERS,
    CDE_UNLOCKHYPERMODE,
    CDE_ALL
} Code;

typedef enum __Game {
    GME_INVALID = -1,
    GME_MENU,
    GME_MENU_MP1,
    GME_MENU_MP2,
    GME_MP1,
    GME_MP2,
    GME_MP3,
    GME_MP3_SA,
    GME_MP1_GCN,
    GME_MP1R1_GCN,
    GME_MP1R2_GCN,
    GME_MP2_GCN
} Game;

typedef enum __GameRegion {
    GMR_INVALID = -1,
    GMR_NTSCU,
    GMR_PAL,
    GMR_NTSCJ
} GameRegion;

typedef enum __CodeFormat {
    CFM_INVALID = -1,
    CFM_DOLPHIN,
    CFM_OCARINA,
    CFM_RAW
} CodeFormat;

Code CDE_FromStr(char* str) {
    if (!strcmp(str, TOSTR(CDE_RESTOREBEAMFX)))
        return CDE_RESTOREBEAMFX;
    else if (!strcmp(str, TOSTR(CDE_DISABLEBLOOM)))
        return CDE_DISABLEBLOOM;
    else if (!strcmp(str, TOSTR(CDE_RESTOREDASHING)))
        return CDE_RESTOREDASHING;
    else if (!strcmp(str, TOSTR(CDE_ENABLESKIPCUTSCENE)))
        return CDE_ENABLESKIPCUTSCENE;
    else if (!strcmp(str, TOSTR(CDE_FRIENDVOUCHERS)))
        return CDE_FRIENDVOUCHERS;
    else if (!strcmp(str, TOSTR(CDE_UNLOCKHYPERMODE)))
        return CDE_UNLOCKHYPERMODE;
    else if (!strcmp(str, TOSTR(CDE_ALL)))
        return CDE_ALL;
    else
        return CDE_INVALID;
}

Game GME_FromStr(char* str) {
    if (!strcmp(str, TOSTR(GME_MENU)))
        return GME_MENU;
    else if (!strcmp(str, TOSTR(GME_MENU_MP1)))
        return GME_MENU_MP1;
    else if (!strcmp(str, TOSTR(GME_MENU_MP2)))
        return GME_MENU_MP2;
    else if (!strcmp(str, TOSTR(GME_MP1)))
        return GME_MP1;
    else if (!strcmp(str, TOSTR(GME_MP2)))
        return GME_MP2;
    else if (!strcmp(str, TOSTR(GME_MP3)))
        return GME_MP3;
    else if (!strcmp(str, TOSTR(GME_MP3_SA)))
        return GME_MP3_SA;
    else if (!strcmp(str, TOSTR(GME_MP1_GCN)))
        return GME_MP1_GCN;
    else if (!strcmp(str, TOSTR(GME_MP1R1_GCN)))
        return GME_MP1R1_GCN;
    else if (!strcmp(str, TOSTR(GME_MP1R2_GCN)))
        return GME_MP1R2_GCN;
    else if (!strcmp(str, TOSTR(GME_MP2_GCN)))
        return GME_MP2_GCN;
    else
        return GME_INVALID;
}

GameRegion GMR_FromStr(char* str) {
    if (!strcmp(str, TOSTR(GMR_NTSCU)))
        return GMR_NTSCU;
    else if (!strcmp(str, TOSTR(GMR_PAL)))
        return GMR_PAL;
    else if (!strcmp(str, TOSTR(GMR_NTSCJ)))
        return GMR_NTSCJ;
    else
        return GMR_INVALID;
}

CodeFormat CFM_FromStr(char* str) {
    if (!strcmp(str, TOSTR(CFM_DOLPHIN)))
        return CFM_DOLPHIN;
    else if (!strcmp(str, TOSTR(CFM_OCARINA)))
        return CFM_OCARINA;
    else if (!strcmp(str, TOSTR(CFM_RAW)))
        return CFM_RAW;
    else
        return CFM_INVALID;
}

char* GME_GetName(Game game) {
    switch (game) {
        case GME_MENU:
            return "Menu";
        case GME_MENU_MP1:
            return "Menu MP1";
        case GME_MENU_MP2:
            return "Menu MP2";
        case GME_MP1:
            return "MP1";
        case GME_MP2:
            return "MP2";
        case GME_MP3:
            return "MP3";
        case GME_MP3_SA:
            return "MP3 SA";
        case GME_MP1_GCN:
            return "MP1 GCN";
        case GME_MP1R1_GCN:
            return "MP1R1 GCN";
        case GME_MP1R2_GCN:
            return "MP1R2 GCN";
        case GME_MP2_GCN:
            return "MP2 GCN";
        default:
            return "Invalid";
    }
}

char* GME_GetHeader(Game game, GameRegion region) {
    switch (game) {
        case GME_MENU:
        case GME_MP1:
        case GME_MP2:
        case GME_MP3:
            return "Metroid Prime Trilogy";
        case GME_MENU_MP1:
        case GME_MP1_GCN:
        case GME_MP1R1_GCN:
        case GME_MP1R2_GCN:
            return "Metroid Prime";
        case GME_MENU_MP2:
            return "Metroid Prime 2 Dark Echoes";
        case GME_MP3_SA:
            return "Metroid Prime 3 Corruption";
        case GME_MP2_GCN:
            return region == GMR_NTSCJ ? "Metroid Prime 2 Dark Echoes" : "Metroid Prime 2 Echoes";
        default:
            return "Invalid";
    }
}

char* CDE_GetName(Code code, Game game) {
    char* gameName = GME_GetName(game);
    switch (code) {
        case CDE_RESTOREBEAMFX:
            return csprintf_s("Restore Beam FX (%s) [PrimeHack]", gameName);
        case CDE_DISABLEBLOOM:
            return csprintf_s("Disable Bloom (%s) [PrimeHack]", gameName);
        case CDE_RESTOREDASHING:
            return csprintf_s("Restore Dashing (%s) [PrimeHack]", gameName);
        case CDE_ENABLESKIPCUTSCENE:
            return csprintf_s("Enable Skip Cutscene (%s) [PrimeHack]", gameName);
        case CDE_FRIENDVOUCHERS:
            return csprintf_s("Remove Friend Vouchers Requirement (%s) [PrimeHack]", gameName);
        case CDE_UNLOCKHYPERMODE:
            return csprintf_s("Unlock Hypermode Difficulty (%s) [PrimeHack]", gameName);
        case CDE_ALL:
            return csprintf_s("%s", "All");
        default:
            return csprintf_s("%s", "Invalid");
    }
}

int printcode(Code code, Game game, GameRegion region, CodeFormat format, uint8_t* header, uint8_t prntnl) {
    uint32_t val_game_sig = 0x00000000, addr_game_sig2_mp3 = 0x00000000;
    uint16_t val_id1 = 0x00, val_id2 = 0x00, val_id3 = 0x00, val_version_mp1 = 0x0000;
    
    switch (game) {
        case GME_MENU:
            if (region == GMR_NTSCU) {
                val_game_sig = 0x38000018;
                val_id1  = 0x5233; // R3
                val_id2  = 0x4D45; // ME
                val_id3  = 0x3031; // 01
            } else if (region == GMR_PAL) {
                val_game_sig = 0x7C0000D0;
                val_id1  = 0x5233; // R3
                val_id2  = 0x4D50; // MP
                val_id3  = 0x3031; // 01
            } else { // region == GMR_NTSCJ
                fprintf(stderr, "ERROR: There is no NTSCJ release of Metroid Prime: Trilogy.\n");
                return MCS_INVLDARG;
            }
            
            break;
        case GME_MENU_MP1:
            if (region == GMR_NTSCJ) {
                val_game_sig = 0x806DDAEC;
                val_id1  = 0x5233; // R3
                val_id2  = 0x494A; // IJ
                val_id3  = 0x3031; // 01
            } else { // region == GMR_PAL || region == GMR_NTSCJ
                fprintf(stderr, "ERROR: There is no NTSCU and PAL release of Metroid Prime New Play Controls.\n");
                return MCS_INVLDARG;
            }
            
            break;
        case GME_MENU_MP2:
            if (region == GMR_NTSCJ) {
                val_game_sig = 0x801E0000;
                val_id1  = 0x5233; // R3
                val_id2  = 0x324A; // 2J
                val_id3  = 0x3031; // 01
            } else { // region == GMR_PAL || region == GMR_NTSCJ
                fprintf(stderr, "ERROR: There is no NTSCU and PAL release of Metroid Prime 2: Dark Echoes New Play "
                    "Controls\n");
                return MCS_INVLDARG;
            }
            
            break;
        case GME_MP1:
            if (region == GMR_NTSCU) {
                val_game_sig = 0x4E800020;
                val_id1  = 0x5233; // R3
                val_id2  = 0x4D45; // ME
                val_id3  = 0x3031; // 01
            } else if (region == GMR_PAL) {
                val_game_sig = 0x7C962378;
                val_id1  = 0x5233; // R3
                val_id2  = 0x4D50; // MP
                val_id3  = 0x3031; // 01
            } else { // region == GMR_NTSCJ
                val_game_sig = 0x53687566;
                val_id1  = 0x5233; // R3
                val_id2  = 0x494A; // IJ
                val_id3  = 0x3031; // 01
            }
            
            break;
        case GME_MP2:
            if (region == GMR_NTSCU) {
                val_game_sig = 0x4BFF64E1;
                val_id1  = 0x5233; // R3
                val_id2  = 0x4D45; // ME
                val_id3  = 0x3031; // 01
            } else if (region == GMR_PAL) {
                val_game_sig = 0x80830000;
                val_id1  = 0x5233; // R3
                val_id2  = 0x4D50; // MP
                val_id3  = 0x3031; // 01
            } else { // region == GMR_NTSCJ
                val_game_sig = 0x936DAABC;
                val_id1  = 0x5233; // R3
                val_id2  = 0x324A; // 2J
                val_id3  = 0x3031; // 01
            }
            
            break;
        case GME_MP3:
            if (region == GMR_NTSCU) {
                val_game_sig = 0x80010070;
                val_id1  = 0x5233; // R3
                val_id2  = 0x4D45; // ME
                val_id3  = 0x3031; // 01
                addr_game_sig2_mp3 = 0x80576AE8;
            } else if (region == GMR_PAL) {
                val_game_sig = 0x3A800000;
                val_id1  = 0x5233; // R3
                val_id2  = 0x4D50; // MP
                val_id3  = 0x3031; // 01
                addr_game_sig2_mp3 = 0x805795A4;
            } else { // region == GMR_NTSCJ
                fprintf(stderr, "ERROR: There is no NTSCJ release of Metroid Prime: Trilogy.\n");
                return MCS_INVLDARG;
            }
            
            break;
        case GME_MP3_SA:
            if (region == GMR_NTSCU) {
                val_id1  = 0x524D; // RM
                val_id2  = 0x3345; // 3E
                val_id3  = 0x3031; // 01
            } else if (region == GMR_PAL) {
                val_id1  = 0x524D; // RM
                val_id2  = 0x3350; // 3P
                val_id3  = 0x3031; // 01
            } else { // region == GMR_NTSCJ
                val_id1  = 0x524D; // RM
                val_id2  = 0x334A; // 3J
                val_id3  = 0x3031; // 01
            }
            
            break;
        case GME_MP1_GCN:
        case GME_MP1R1_GCN:
        case GME_MP1R2_GCN:
            if (region == GMR_NTSCU) {
                val_id1  = 0x474D; // GM
                val_id2  = 0x3845; // 8E
                val_id3  = 0x3031; // 01
                switch (game) {
                    case GME_MP1_GCN:
                        val_version_mp1 = 0x0000;
                        
                        break;
                    case GME_MP1R1_GCN:
                        val_version_mp1 = 0x0001;
                        
                        break;
                    case GME_MP1R2_GCN:
                        val_version_mp1 = 0x0002;
                        
                        break;
                    default:
                        fprintf(stderr, "Invalid game specified.");
                        return MCS_INVLDARG;
                }
            } else if (region == GMR_PAL) {
                val_id1  = 0x474D; // GM
                val_id2  = 0x3850; // 8P
                val_id3  = 0x3031; // 01
            } else { // region == GMR_NTSCJ
                val_id1  = 0x474D; // GM
                val_id2  = 0x384A; // 8J
                val_id3  = 0x3031; // 01
            }
            
            break;
        case GME_MP2_GCN:
            if (region == GMR_NTSCU) {
                val_id1  = 0x4732; // G2
                val_id2  = 0x4D45; // ME
                val_id3  = 0x3031; // 01
            } else if (region == GMR_PAL) {
                val_id1  = 0x4732; // G2
                val_id2  = 0x4D50; // MP
                val_id3  = 0x3031; // 01
            } else { // region == GMR_NTSCJ
                val_id1  = 0x4732; // G2
                val_id2  = 0x4D4A; // MJ
                val_id3  = 0x3031; // 01
            }
            
            break;
        default:
            fprintf(stderr, "Invalid game specified.");
            return MCS_INVLDARG;
    }
    
    uint32_t addr_exception_hook = 0x80000048,
        addr_game_sig = 0x8046D340,
        addr_game_id = 0x80000000,
        addr_memstart = 0x80000000,
        addr_version_mp1 = 0x80000006, // (actually is disc number but use it to check itself + next byte for version)
        val_game_sig2_mp3 = 0x7D415378;
    
    if (format != CFM_RAW) {
        if (*header) {
            *header = 0;
            if (format == CFM_OCARINA) {
                printf("%c%c%c%c%c%c\n", val_id1 >> 8, val_id1, val_id2 >> 8, val_id2, val_id3 >> 8, val_id3);
                printf("%s\n\n", GME_GetHeader(game, region));
            } else
                printf("[Gecko]\n");
        }
        if (format == CFM_DOLPHIN)
            printf("$");
        char* codeName = CDE_GetName(code, game);
        if (codeName) {
            printf("%s\n", codeName);
            free(codeName);
        } else {
            fprintf(stderr, "ERROR: Failed to print and free codeName from heap; codeName is NUL.\n");
            return MCS_ERROR;
        }
    }
    
    if16(IF_EQU, 0, addr_game_id, val_id1);
    if16e(IF_EQU, 0, addr_game_id + 0x00000002, val_id2);
    if16e(IF_EQU, 0, addr_game_id + 0x00000004, val_id3);
    if32e(IF_NEQ, 0, addr_exception_hook, 0x00000000);
    // There is no way to do a byte check in Gecko, so do a short check instead. This starts from the disc number
    // address then reads to the disc version address (0x80000006 to 0x80000007). Trilogy and (usually) other games
    // have a single disc. This means the disc number has a value of 0x00. This makes this short check safe (0x00XX,
    // XX being the version).
    if (val_version_mp1)
        if16e(IF_EQU, 0, addr_version_mp1, val_version_mp1);
    if (val_game_sig)
        if32e(IF_EQU, 0, addr_game_sig, val_game_sig);
    if (addr_game_sig2_mp3)
        if32e(IF_EQU, 0, addr_game_sig2_mp3, val_game_sig2_mp3);
    
    switch (code) {
        case CDE_RESTOREBEAMFX:
            uint32_t gunfx_offset = 0x00000000,
                transform_ctor_offset = 0x00000000,
                advance_particles_offset = 0x00000000;
            if (game == GME_MP1) {
                if (region == GMR_NTSCU) {
                    gunfx_offset = 0xFFFFFD68;
                    transform_ctor_offset = 0xAC;
                    advance_particles_offset = 0xFFFFFEB0;
                } else if (region == GMR_PAL) {
                    gunfx_offset = 0;
                    transform_ctor_offset = 0;
                    advance_particles_offset = 0;
                } else { // region == GMR_NTSCJ
                    gunfx_offset = 0x8E8;
                    transform_ctor_offset = 0xFFFFFB70;
                    advance_particles_offset = 0x4B0;
                }
            } else {
                fprintf(stderr, "ERROR: Code \"CDE_RESTOREBEAMFX\" is only available for Metroid Prime on Wii.\n");
                return MCS_INVLDARG;
            }
            
            uint32_t bf_address1 = 0x80004A68, bf_address2 = 0x80004968;
            
            write32(0, bf_address1, 0x9421FFA8);
            write32(0, bf_address1 + 0x4, 0x7C0802A6);
            write32(0, bf_address1 + 0x8, 0x9001001C);
            write32(0, bf_address1 + 0xC, 0x93A10010);
            write32(0, bf_address1 + 0x10, 0x93C10018);
            write32(0, bf_address1 + 0x14, 0x93E10014);
            write32(0, bf_address1 + 0x18, 0xD3E1000C);
            write32(0, bf_address1 + 0x1C, 0x7C7F1B78);
            write32(0, bf_address1 + 0x20, 0x7C9E2378);
            write32(0, bf_address1 + 0x24, 0x7CBD2B78);
            write32(0, bf_address1 + 0x28, 0xFFE00890);
            write32(0, bf_address1 + 0x2C, 0x38610020);
            write32(0, bf_address1 + 0x30, 0x389F04B0);
            write32(0, bf_address1 + 0x34, 0x483441E5 + transform_ctor_offset);
            write32(0, bf_address1 + 0x38, 0x7FA3EB78);
            write32(0, bf_address1 + 0x3C, 0x38810020);
            write32(0, bf_address1 + 0x40, 0x7FE5FB78);
            write32(0, bf_address1 + 0x44, 0x48134F15 + advance_particles_offset);
            write32(0, bf_address1 + 0x48, 0xC03F0384);
            write32(0, bf_address1 + 0x4C, 0x38800000);
            write32(0, bf_address1 + 0x50, 0xC002CDF8);
            write32(0, bf_address1 + 0x54, 0x807F0734);
            write32(0, bf_address1 + 0x58, 0xFC010040);
            write32(0, bf_address1 + 0x5C, 0x40810018);
            write32(0, bf_address1 + 0x60, 0xC03F037C);
            write32(0, bf_address1 + 0x64, 0xC002D078);
            write32(0, bf_address1 + 0x68, 0xFC010040);
            write32(0, bf_address1 + 0x6C, 0x40810008);
            write32(0, bf_address1 + 0x70, 0x38800001);
            write32(0, bf_address1 + 0x74, 0x81830000);
            write32(0, bf_address1 + 0x78, 0x7FC5F378);
            write32(0, bf_address1 + 0x7C, 0x38DF0510);
            write32(0, bf_address1 + 0x80, 0xFC20F890);
            write32(0, bf_address1 + 0x84, 0x818C001C);
            write32(0, bf_address1 + 0x88, 0x7D8903A6);
            write32(0, bf_address1 + 0x8C, 0x4E800421);
            write32(0, bf_address1 + 0x90, 0x83A10010);
            write32(0, bf_address1 + 0x94, 0x83C10018);
            write32(0, bf_address1 + 0x98, 0x83E10014);
            write32(0, bf_address1 + 0x9C, 0x8001001C);
            write32(0, bf_address1 + 0xA0, 0xC3E1000C);
            write32(0, bf_address1 + 0xA4, 0x7C0803A6);
            write32(0, bf_address1 + 0xA8, 0x38210058);
            write32(0, bf_address1 + 0xAC, 0x4E800020);
            
            write32(0, bf_address2, 0x7F03C378);
            write32(0, bf_address2 + 0x4, 0x7F24CB78);
            write32(0, bf_address2 + 0x8, 0x7F65DB78);
            write32(0, bf_address2 + 0xC, 0xFC20F890);
            write32(0, bf_address2 + 0x10, 0x480000F1);
            write32(0, bf_address2 + 0x14, 0x386100B0);
            write32(0, bf_address2 + 0x18, 0x48187D2C + gunfx_offset);
            
            write32(0, 0x8018C6A8 + gunfx_offset, 0x4BE782C0 - gunfx_offset);
            
            break;
        case CDE_DISABLEBLOOM:
            if (game == GME_MP1) {
                if (region == GMR_NTSCU) {
                    write32(0, 0x80290EDC, 0x4E800020);
                } else if (region == GMR_PAL) {
                    write32(0, 0x80291258, 0x4E800020);
                } else { // region == GMR_NTSCJ
                    write32(0, 0x802919BC, 0x4E800020);
                }
            } else if (game == GME_MP2) {
                if (region == GMR_NTSCU) {
                    write32(0, 0x80292204, 0x4E800020);
                } else if (region == GMR_PAL) {
                    write32(0, 0x80294A40, 0x4E800020);
                } else { // region == GMR_NTSCJ
                    write32(0, 0x8029137C, 0x4E800020);
                }
            } else {
                fprintf(stderr, ("ERROR: Code \"CDE_DISABLEBLOOM\" is only available for Metroid Prime and Metroid "
                    "Prime 2: Echoes on Wii.\n"));
                return MCS_INVLDARG;
            }
            
            break;
        case CDE_RESTOREDASHING:
            switch (game) {
                case GME_MP1:
                    if (region == GMR_NTSCU) {
                        write32(0, 0x80193334, 0x48000018);
                        write32(0, 0x80194B60, 0x4800001C);
                        write32(0, 0x80192CC0, 0x881F037C);
                    } else if (region == GMR_PAL) {
                        write32(0, 0x801935CC, 0x48000018);
                        write32(0, 0x80194DF8, 0x4800001C);
                        write32(0, 0x80192F58, 0x881F037C);
                    } else { // region == GMR_NTSCJ
                        write32(0, 0x80193EB4, 0x48000018);
                        write32(0, 0x801956E0, 0x4800001C);
                        write32(0, 0x80193840, 0x881F037C);
                    }
                    
                    break;
                case GME_MP1_GCN:
                    if (region == GMR_PAL)
                        write32(0, 0x80275328, 0x48000018);
                    else if (region == GMR_NTSCJ)
                        write32(0, 0x802770E4, 0x48000018);
                    else { // region == GMR_NTSCJ
                        fprintf(stderr, "ERROR: Code \"CDE_RESTOREDASHING\" is not available for NTSCJ Metroid Prime "
                            "on GameCube\n");
                        return MCS_ERROR;
                    }
                    
                    break;
                case GME_MP1R2_GCN:
                    write32(0, 0x802888D0, 0x48000018);
                    
                    break;
                case GME_MP2:
                    if (region == GMR_NTSCU) {
                        write32(0, 0x8015D690, 0x60000000);
                        write32(0, 0x8015CD1C, 0x881E0574);
                    } else if (region == GMR_PAL) {
                        write32(0, 0x8015EE08, 0x60000000);
                        write32(0, 0x8015E494, 0x881E0574);
                    } else { // region == GMR_NTSCJ
                        write32(0, 0x8015CC58, 0x60000000);
                        write32(0, 0x8015C2E4, 0x881E0574);
                    }
                    
                    break;
                case GME_MP2_GCN:
                    if (region == GMR_NTSCU) {
                        write32(0, 0x8018961C, 0x60000000);
                        write32(0, 0x80189D6C, 0x881E0588);
                    } else if (region == GMR_PAL) {
                        write32(0, 0x80189914, 0x60000000);
                        write32(0, 0x8018A068, 0x881E0588);
                    } else { // region == GMR_NTSCJ
                        write32(0, 0x8018B130, 0x60000000);
                        write32(0, 0x8018B884, 0x881E0588);
                    }
                    
                    break;
                case GME_MP3:
                    if (region == GMR_NTSCU) {
                        write32(0, 0x80174C60, 0x60000000);
                        write32(0, 0x8017432C, 0x881E06D0);
                    } else if (region == GMR_PAL) {
                        write32(0, 0x801745AC, 0x60000000);
                        write32(0, 0x80173C78, 0x881E06D0);
                    } else { // region == GMR_NTSCJ
                        fprintf(stderr, "ERROR: Code \"CDE_RESTOREDASHING\" is not available for NTSCJ Metroid Prime "
                            "3: Corruption on Wii\n");
                        return MCS_ERROR;
                    }
                    
                    break;
                case GME_MP3_SA:
                    if (region == GMR_NTSCU) {
                        write32(0, 0x80178D90, 0x60000000);
                        write32(0, 0x8017845C, 0x881E06CC);
                    } else if (region == GMR_PAL) {
                        write32(0, 0x80179884, 0x60000000);
                        write32(0, 0x80178F50, 0x881E06D0);
                    } else {  // region == GMR_NTSCJ
                        write32(0, 0x8017AA90, 0x60000000);
                        write32(0, 0x8017A15C, 0x881E06D0);
                    }
                    
                    break;
                default:
                    fprintf(stderr, "ERROR: Code \"CDE_RESTOREDASHING\" is only available for Metroid Prime and "
                        "Metroid Prime 2: Echoes on Wii and GameCube aswell as Metroid Prime 3: Corruption on Wii.\n");
                    return MCS_ERROR;
            }
            
            break;
        case CDE_ENABLESKIPCUTSCENE:
            switch (game) {
                uint32_t sc_address1;
                case GME_MP1:
                    if (region == GMR_NTSCU) {
                        sc_address1 = 0x800CF054;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    } else if (region == GMR_PAL) {
                        sc_address1 = 0x800CF174;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    } else if (region == GMR_NTSCJ) {
                        sc_address1 = 0x800CF3E4;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    }
                    
                    break;
                case GME_MP1_GCN:
                    if (region == GMR_NTSCU) {
                        sc_address1 = 0x801D5528;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    } else if (region == GMR_PAL) {
                        sc_address1 = 0x801C6640;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    } else { // region == GMR_NTSCJ
                        fprintf(stderr, "ERROR: Code \"CDE_ENABLESKIPCUTSCENE\" is not available for NTSCJ Metroid "
                            "Prime on GameCube\n");
                        return MCS_INVLDARG;
                    }
                    
                    break;
                case GME_MP1R1_GCN:
                    sc_address1 = 0x8015204C;
                    write32(0, sc_address1 + 0x00, 0x38600001);
                    write32(0, sc_address1 + 0x04, 0x4E800020);
                    
                    break;
                case GME_MP1R2_GCN:
                    sc_address1 = 0x801D5D78;
                    write32(0, sc_address1 + 0x00, 0x38600001);
                    write32(0, sc_address1 + 0x04, 0x4E800020);
                    
                    break;
                case GME_MP2:
                    if (region == GMR_NTSCU) {
                        sc_address1 = 0x800BC4D0;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    } else if (region == GMR_PAL) {
                        sc_address1 = 0x800BDB9C;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    } else if (region == GMR_NTSCJ) {
                        sc_address1 = 0x800BBB68;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    }
                    
                    break;
                case GME_MP2_GCN:
                    if (region == GMR_NTSCU) {
                        sc_address1 = 0x80142340;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    } else if (region == GMR_NTSCJ) {
                        sc_address1 = 0x80143330;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    } else if (region == GMR_PAL) {
                        sc_address1 = 0x8014257C;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    }
                    
                    break;
                case GME_MP3:
                    if (region == GMR_NTSCU) {
                        sc_address1 = 0x800B9F30;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    } else if (region == GMR_PAL) {
                        sc_address1 = 0x800B9F30;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    } else { // region == GMR_NTSCJ
                        fprintf(stderr, "ERROR: Code \"CDE_ENABLESKIPCUTSCENE\" is not available for NTSCJ Metroid "
                            "Prime 3: Corruption on Wii\n");
                        return MCS_INVLDARG;
                    }
                    
                    break;
                case GME_MP3_SA:
                    if (region == GMR_NTSCU) {
                        sc_address1 = 0x800BB930;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    } else if (region == GMR_PAL) {
                        sc_address1 = 0x800BBD24;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    } else if (region == GMR_NTSCJ) {
                        sc_address1 = 0x800BC10C;
                        write32(0, sc_address1 + 0x00, 0x38600001);
                        write32(0, sc_address1 + 0x04, 0x4E800020);
                    }
                    
                    break;
                default:
                    fprintf(stderr, "ERROR: Code \"CDE_ENABLESKIPCUTSCENE\" is only available for Metroid Prime and "
                        "Metroid Prime 2: Echoes on Wii and GameCube aswell as Metroid Prime 3: Corruption on Wii.\n");
                    return MCS_INVLDARG;
            }
            
            break;
        case CDE_FRIENDVOUCHERS:
            uint32_t addr_extras_arr;
            if (game == GME_MENU) {
                if (region == GMR_NTSCU)
                    addr_extras_arr = 0x8052DBB0;
                else if (region == GMR_PAL)
                    addr_extras_arr = 0x805320A0;
                else { // region == GMR_NTSCJ
                    fprintf(stderr, "ERROR: Code \"CDE_FRIENDVOUCHERS\" is only available for Metroid Prime: Trilogy "
                        "Menu on Wii.\n");
                    return MCS_INVLDARG;
                }
            } else {
                fprintf(stderr, "ERROR: Code \"CDE_FRIENDVOUCHERS\" is only available for Metroid Prime: Trilogy Menu "
                    "on Wii.\n");
                return MCS_INVLDARG;
            }
            
            /*
; Set r11 to extras_arr_addr
lis r11, extras_arr_addr
ori r11, r11, extras_arr_addr
; Load word from r11 to r0
lwz r0, 0 (r11)
; Shift r0 28 bits to the right
srwi r0, r0, 28
; Compare r0 with 0x00000008
cmplwi cr7, r0, 0x0008
; Branch back to LR if r0 != 0x00000008
; LR is set by Gecko
bnelr cr7

; Set r0 to 0x03000102
lis r0, 0x0300
ori r0, r0, 0x0102
; Store r0 as word to (r11 + 0x430)
stw r0, 0x430 (r11)
; Set r0 to 0x00000000 + 0x0002 (2)
addi r0, r0, 0x0002
; Store r0 as word to (r11 + 0x434)
stw r0, 0x434 (r11)

; Set r0 to 0x00000000 + 0x0069 (105)
addi r0, r0, 0x0069
; Set CTR to r0
mtctr r0
; Set r0 to 0x00000000 + 0x0000 (0)
addi r0, r0, 0x0000
; Start loop
loop:
  ; Store r0 as byte to (r11 + 7) (7th byte of r11)
  stb r0, 7 (r11)
  ; Add 12 to r11 (for next 12 bytes)
  addi r11, r11, 12
  ; Loop if CTR != 0x0000000000000000
  bdnz loop

; Branch back to LR
; LR is set by Gecko
blr
           */
            uint32_t fv_ppcasm[18] = {
                0x3D600000 | ((addr_extras_arr & ~0x0000FFFF) >> 16),
                0x616B0000 | (addr_extras_arr & ~0xFFFF0000),
                0x800B0000,
                0x5400273E,
                0x2B800008,
                0x4C9E0020,
                0x3C000300,
                0x60000102,
                0x900B0430,
                0x38000002,
                0x900B0434,
                0x38000069,
                0x7C0903A6,
                0x38000000,
                0x980B0007,
                0x396B000C,
                0x4200FFF8,
                0x4E800020
            };
            runppcasm(18, fv_ppcasm);
            
            break;
        case CDE_UNLOCKHYPERMODE:
            int16_t val_r13_offset;
            if (game == GME_MENU) {
                if (region == GMR_NTSCU)
                    val_r13_offset = -0x2F94;
                else if (region == GMR_PAL)
                    val_r13_offset = -0x2F34;
                else { // region == GMR_NTSCJ
                    fprintf(stderr, "ERROR: Code \"CDE_UNLOCKHYPERMODE\" is only available for Metroid Prime: Trilogy "
                        "Menu on Wii.\n");
                    return MCS_INVLDARG;
                }
            } else {
                fprintf(stderr, "ERROR: Code \"CDE_UNLOCKHYPERMODE\" is only available for Metroid Prime: Trilogy Menu"
                    " on Wii.\n");
                return MCS_INVLDARG;
            }
            
            /*
; Load word from (r13 - r13_offset) to r11
lwz r11, r13_offset (r13)
; Set r0 to r11
mr r0, r11
; Shift r0 28 bits to the right
srwi r0, r0, 28
; Compare r0 with 0x00000008
cmplwi cr7, r0, 0x0008
; Branch back to LR if r0 != 0x00000008
; LR is set by Gecko
bnelr cr7
; Set r0 to 0x00000000 + 0x0001 (1)
addi r0, r0, 0x0001
; Store r0 as byte to (r11 + 0x68)
stb r0, 0x68 (r11)
; Store r0 as byte to (r11 + 0xA0)
stb r0, 0xA0 (r11)
; Store r0 as byte to (r11 + 0xD8)
stb r0, 0xD8 (r11)
; Branch back to LR
; LR is set by Gecko
blr
            */
            uint32_t hm_ppcasm[10] = {
                (val_r13_offset & ~0xFFFF0000) | 0x816D0000,
                0x7D605B78,
                0x5400273E,
                0x2B800008,
                0x4C9E0020,
                0x38000001,
                0x980B0068,
                0x980B00A0,
                0x980B00D8,
                0x4E800020
            };
            runppcasm(10, hm_ppcasm);
            
            break;
        default:
            fprintf(stderr, "Invalid code specified.");
            return MCS_INVLDARG;
    }
    
    endifv(0, (addr_memstart >> 16), (addr_memstart >> 16));
    
    if (prntnl)
        printf("\n");
    
    return MCS_SUCCESS;
}

int main(int argc, char** argv) {
    if (argc < 5) {
        fprintf(stderr, "makecode by Yonder (original logic of codes by PrimeHack team) 2022\n"
               "makecode is a cli that prints PrimeHack's mods ported to Gecko codes.\n"
               "Usage:\n"
               "  %s <code> <game> <region> <format>\n"
               "    code - Code to print. See \"Codes\" below for more info.\n"
               "    game - Which game to print the code for. See \"Games\" below for more info.\n"
               "    region - Which region the game is for. See \"Regions\" below for more info.\n"
               "    format - Which format to print the code to. See \"Formats\" below for more info.\n"
               "Codes:\n"
               "  CDE_RESTOREBEAMFX\n"
               "  CDE_DISABLEBLOOM\n"
               "  CDE_RESTOREDASHING\n"
               "  CDE_ENABLESKIPCUTSCENE\n"
               "  CDE_FRIENDVOUCHERS\n"
               "  CDE_UNLOCKHYPERMODE\n"
               "  CDE_ALL\n"
               "Games:\n"
               "  GME_MENU\n"
               "  GME_MENU_MP1\n"
               "  GME_MENU_MP2\n"
               "  GME_MP1\n"
               "  GME_MP2\n"
               "  GME_MP3\n"
               "  GME_MP3_SA\n"
               "  GME_MP1_GCN\n"
               "  GME_MP1R1_GCN\n"
               "  GME_MP1R2_GCN\n"
               "  GME_MP2_GCN\n"
               "Regions:\n"
               "  GMR_NTSCU\n"
               "  GMR_PAL\n"
               "  GMR_NTSCJ\n"
               "Formats:\n"
               "  CFM_DOLPHIN\n"
               "  CFM_OCARINA\n"
               "  CFM_RAW\n",
               argv[0]);
        return MCS_ERROR;
    }
    
    Code code = CDE_FromStr(argv[1]);
    Game game = GME_FromStr(argv[2]);
    GameRegion region = GMR_FromStr(argv[3]);
    CodeFormat format = CFM_FromStr(argv[4]);
    if (code == CDE_INVALID) {
        fprintf(stderr, "ERROR: Invalid argument for \"code\"\n");
        return MCS_INVLDARG;
    } else if (game == GME_INVALID) {
        fprintf(stderr, "ERROR: Invalid argument for \"game\"\n");
        return MCS_INVLDARG;
    } else if (region == GMR_INVALID) {
        fprintf(stderr, "ERROR: Invalid argument for \"region\"\n");
        return MCS_INVLDARG;
    } else if (format == CFM_INVALID) {
        fprintf(stderr, "ERROR: Invalid argument for \"format\"\n");
        return MCS_INVLDARG;
    }
    
    uint8_t header = 1, prntnl = (format == CFM_OCARINA);
    if (code == CDE_ALL) {
        if (game == GME_MENU_MP1 || game == GME_MENU_MP2) {
            fprintf(stderr, "ERROR: There are no codes available for NTSJ Metroid Prime Menu and Metroid Prime 2: "
                "Dark Echoes Menu on Wii.\n");
            return MCS_INVLDARG;
        } else {
            int ret = MCS_SUCCESS;
            if (game == GME_MENU) {
                if ((ret = printcode(CDE_FRIENDVOUCHERS, game, region, format, &header, prntnl)))
                    return ret;
                if ((ret = printcode(CDE_UNLOCKHYPERMODE, game, region, format, &header, 0)))
                    return ret;
            } else {
                if (game == GME_MP1) {
                    if ((ret = printcode(CDE_RESTOREBEAMFX, game, region, format, &header, prntnl)))
                        return ret;
                }
                if (game == GME_MP1 || game == GME_MP2) {
                    if ((ret = printcode(CDE_DISABLEBLOOM, game, region, format, &header, prntnl)))
                        return ret;
                }
                if (((game == GME_MP1_GCN && region != GMR_NTSCJ) || game != GME_MP1_GCN) &&
                ((game == GME_MP3 && region != GMR_NTSCJ) || game != GME_MP1_GCN)) {
                    if (game != GME_MP1R1_GCN) {
                        if ((ret = printcode(CDE_RESTOREDASHING, game, region, format, &header, prntnl)))
                            return ret;
                    }
                    if ((ret = printcode(CDE_ENABLESKIPCUTSCENE, game, region, format, &header, 0)))
                        return ret;
                }
            }
            return ret;
        }
    } else
        return printcode(code, game, region, format, &header, 0);
}
