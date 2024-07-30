
#include <assert.h>

#include "allegrex/allegrex_vfpu.hpp"

#define MAX_CONTROL_REGISTERS 16
static const char *_vfpu_control_register_names[] = {
    "SPFX",
    "TPFX",
    "DPFX",
    "CC",
    "INF4",
    "RSV5",
    "RSV6",
    "REV",
    "RCX0",
    "RCX1",
    "RCX2",
    "RCX3",
    "RCX4",
    "RCX5",
    "RCX6",
    "RCX7", 
};

static const char *_vfpu_register_names[4][128] = {
    { // Single
        "S000", // 0
        "S010", // 1
        "S020", // 2
        "S030", // 3
        "S100", // 4
        "S110", // 5
        "S120", // 6
        "S130", // 7
        "S200", // 8
        "S210", // 9
        "S220", // 10
        "S230", // 11
        "S300", // 12
        "S310", // 13
        "S320", // 14
        "S330", // 15
        "S400", // 16
        "S410", // 17
        "S420", // 18
        "S430", // 19
        "S500", // 20
        "S510", // 21
        "S520", // 22
        "S530", // 23
        "S600", // 24
        "S610", // 25
        "S620", // 26
        "S630", // 27
        "S700", // 28
        "S710", // 29
        "S720", // 30
        "S730", // 31
        "S001", // 32
        "S011", // 33
        "S021", // 34
        "S031", // 35
        "S101", // 36
        "S111", // 37
        "S121", // 38
        "S131", // 39
        "S201", // 40
        "S211", // 41
        "S221", // 42
        "S231", // 43
        "S301", // 44
        "S311", // 45
        "S321", // 46
        "S331", // 47
        "S401", // 48
        "S411", // 49
        "S421", // 50
        "S431", // 51
        "S501", // 52
        "S511", // 53
        "S521", // 54
        "S531", // 55
        "S601", // 56
        "S611", // 57
        "S621", // 58
        "S631", // 59
        "S701", // 60
        "S711", // 61
        "S721", // 62
        "S731", // 63
        "S002", // 64
        "S012", // 65
        "S022", // 66
        "S032", // 67
        "S102", // 68
        "S112", // 69
        "S122", // 70
        "S132", // 71
        "S202", // 72
        "S212", // 73
        "S222", // 74
        "S232", // 75
        "S302", // 76
        "S312", // 77
        "S322", // 78
        "S332", // 79
        "S402", // 80
        "S412", // 81
        "S422", // 82
        "S432", // 83
        "S502", // 84
        "S512", // 85
        "S522", // 86
        "S532", // 87
        "S602", // 88
        "S612", // 89
        "S622", // 90
        "S632", // 91
        "S702", // 92
        "S712", // 93
        "S722", // 94
        "S732", // 95
        "S003", // 96
        "S013", // 97
        "S023", // 98
        "S033", // 99
        "S103", // 100
        "S113", // 101
        "S123", // 102
        "S133", // 103
        "S203", // 104
        "S213", // 105
        "S223", // 106
        "S233", // 107
        "S303", // 108
        "S313", // 109
        "S323", // 110
        "S333", // 111
        "S403", // 112
        "S413", // 113
        "S423", // 114
        "S433", // 115
        "S503", // 116
        "S513", // 117
        "S523", // 118
        "S533", // 119
        "S603", // 120
        "S613", // 121
        "S623", // 122
        "S633", // 123
        "S703", // 124
        "S713", // 125
        "S723", // 126
        "S733", // 127
    },

    { // Double
        "C000", // 0
        "C010", // 1
        "C020", // 2
        "C030", // 3
        "C100", // 4
        "C110", // 5
        "C120", // 6
        "C130", // 7
        "C200", // 8
        "C210", // 9
        "C220", // 10 
        "C230", // 11 
        "C300", // 12 
        "C310", // 13 
        "C320", // 14 
        "C330", // 15 
        "C400", // 16 
        "C410", // 17 
        "C420", // 18 
        "C430", // 19 
        "C500", // 20 
        "C510", // 21 
        "C520", // 22 
        "C530", // 23 
        "C600", // 24 
        "C610", // 25 
        "C620", // 26 
        "C630", // 27 
        "C700", // 28 
        "C710", // 29 
        "C720", // 30 
        "C730", // 31 
        "R000", // 32 
        "R001", // 33 
        "R002", // 34 
        "R003", // 35 
        "R100", // 36 
        "R101", // 37 
        "R102", // 38 
        "R103", // 39 
        "R200", // 40 
        "R201", // 41 
        "R202", // 42 
        "R203", // 43 
        "R300", // 44 
        "R301", // 45 
        "R302", // 46 
        "R303", // 47 
        "R400", // 48 
        "R401", // 49 
        "R402", // 50 
        "R403", // 51 
        "R500", // 52 
        "R501", // 53 
        "R502", // 54 
        "R503", // 55 
        "R600", // 56 
        "R601", // 57 
        "R602", // 58 
        "R603", // 59 
        "R700", // 60 
        "R701", // 61 
        "R702", // 62 
        "R703", // 63 
        "C002", // 64 
        "C012", // 65 
        "C022", // 66 
        "C032", // 67 
        "C102", // 68 
        "C112", // 69 
        "C122", // 70 
        "C132", // 71 
        "C202", // 72 
        "C212", // 73 
        "C222", // 74 
        "C232", // 75 
        "C302", // 76 
        "C312", // 77 
        "C322", // 78 
        "C332", // 79 
        "C402", // 80 
        "C412", // 81 
        "C422", // 82 
        "C432", // 83 
        "C502", // 84 
        "C512", // 85 
        "C522", // 86 
        "C532", // 87 
        "C602", // 88 
        "C612", // 89 
        "C622", // 90 
        "C632", // 91 
        "C702", // 92 
        "C712", // 93 
        "C722", // 94 
        "C732", // 95 
        "R020", // 96 
        "R021", // 97 
        "R022", // 98 
        "R023", // 99 
        "R120", // 100
        "R121", // 101
        "R122", // 102
        "R123", // 103
        "R220", // 104
        "R221", // 105
        "R222", // 106
        "R223", // 107
        "R320", // 108
        "R321", // 109
        "R322", // 110
        "R323", // 111
        "R420", // 112
        "R421", // 113
        "R422", // 114
        "R423", // 115
        "R520", // 116
        "R521", // 117
        "R522", // 118
        "R523", // 119
        "R620", // 120
        "R621", // 121
        "R622", // 122
        "R623", // 123
        "R720", // 124
        "R721", // 125
        "R722", // 126
        "R723", // 127
    },

    { // Triple
        "C000", // 0
        "C010", // 1
        "C020", // 2
        "C030", // 3
        "C100", // 4
        "C110", // 5
        "C120", // 6
        "C130", // 7
        "C200", // 8
        "C210", // 9
        "C220", // 10
        "C230", // 11
        "C300", // 12
        "C310", // 13
        "C320", // 14
        "C330", // 15
        "C400", // 16
        "C410", // 17
        "C420", // 18
        "C430", // 19
        "C500", // 20
        "C510", // 21
        "C520", // 22
        "C530", // 23
        "C600", // 24
        "C610", // 25
        "C620", // 26
        "C630", // 27
        "C700", // 28
        "C710", // 29
        "C720", // 30
        "C730", // 31
        "R000", // 32
        "R001", // 33
        "R002", // 34
        "R003", // 35
        "R100", // 36
        "R101", // 37
        "R102", // 38
        "R103", // 39
        "R200", // 40
        "R201", // 41
        "R202", // 42
        "R203", // 43
        "R300", // 44
        "R301", // 45
        "R302", // 46
        "R303", // 47
        "R400", // 48
        "R401", // 49
        "R402", // 50
        "R403", // 51
        "R500", // 52
        "R501", // 53
        "R502", // 54
        "R503", // 55
        "R600", // 56
        "R601", // 57
        "R602", // 58
        "R603", // 59
        "R700", // 60
        "R701", // 61
        "R702", // 62
        "R703", // 63
        "C001", // 64
        "C011", // 65
        "C021", // 66
        "C031", // 67
        "C101", // 68
        "C111", // 69
        "C121", // 70
        "C131", // 71
        "C201", // 72
        "C211", // 73
        "C221", // 74
        "C231", // 75
        "C301", // 76
        "C311", // 77
        "C321", // 78
        "C331", // 79
        "C401", // 80
        "C411", // 81
        "C421", // 82
        "C431", // 83
        "C501", // 84
        "C511", // 85
        "C521", // 86
        "C531", // 87
        "C601", // 88
        "C611", // 89
        "C621", // 90
        "C631", // 91
        "C701", // 92
        "C711", // 93
        "C721", // 94
        "C731", // 95
        "R010", // 96
        "R011", // 97
        "R012", // 98
        "R013", // 99
        "R110", // 100
        "R111", // 101
        "R112", // 102
        "R113", // 103
        "R210", // 104
        "R211", // 105
        "R212", // 106
        "R213", // 107
        "R310", // 108
        "R311", // 109
        "R312", // 110
        "R313", // 111
        "R410", // 112
        "R411", // 113
        "R412", // 114
        "R413", // 115
        "R510", // 116
        "R511", // 117
        "R512", // 118
        "R513", // 119
        "R610", // 120
        "R611", // 121
        "R612", // 122
        "R613", // 123
        "R710", // 124
        "R711", // 125
        "R712", // 126
        "R713", // 127
    },

    { // Quad
        "C000", // 0
        "C010", // 1
        "C020", // 2
        "C030", // 3
        "C100", // 4
        "C110", // 5
        "C120", // 6
        "C130", // 7
        "C200", // 8
        "C210", // 9
        "C220", // 10
        "C230", // 11
        "C300", // 12
        "C310", // 13
        "C320", // 14
        "C330", // 15
        "C400", // 16
        "C410", // 17
        "C420", // 18
        "C430", // 19
        "C500", // 20
        "C510", // 21
        "C520", // 22
        "C530", // 23
        "C600", // 24
        "C610", // 25
        "C620", // 26
        "C630", // 27
        "C700", // 28
        "C710", // 29
        "C720", // 30
        "C730", // 31
        "R000", // 32
        "R001", // 33
        "R002", // 34
        "R003", // 35
        "R100", // 36
        "R101", // 37
        "R102", // 38
        "R103", // 39
        "R200", // 40
        "R201", // 41
        "R202", // 42
        "R203", // 43
        "R300", // 44
        "R301", // 45
        "R302", // 46
        "R303", // 47
        "R400", // 48
        "R401", // 49
        "R402", // 50
        "R403", // 51
        "R500", // 52
        "R501", // 53
        "R502", // 54
        "R503", // 55
        "R600", // 56
        "R601", // 57
        "R602", // 58
        "R603", // 59
        "R700", // 60
        "R701", // 61
        "R702", // 62
        "R703", // 63
        "C002", // 64
        "C012", // 65
        "C022", // 66
        "C032", // 67
        "C102", // 68
        "C112", // 69
        "C122", // 70
        "C132", // 71
        "C202", // 72
        "C212", // 73
        "C222", // 74
        "C232", // 75
        "C302", // 76
        "C312", // 77
        "C322", // 78
        "C332", // 79
        "C402", // 80
        "C412", // 81
        "C422", // 82
        "C432", // 83
        "C502", // 84
        "C512", // 85
        "C522", // 86
        "C532", // 87
        "C602", // 88
        "C612", // 89
        "C622", // 90
        "C632", // 91
        "C702", // 92
        "C712", // 93
        "C722", // 94
        "C732", // 95
        "R020", // 96
        "R021", // 97
        "R022", // 98
        "R023", // 99
        "R120", // 100
        "R121", // 101
        "R122", // 102
        "R123", // 103
        "R220", // 104
        "R221", // 105
        "R222", // 106
        "R223", // 107
        "R320", // 108
        "R321", // 109
        "R322", // 110
        "R323", // 111
        "R420", // 112
        "R421", // 113
        "R422", // 114
        "R423", // 115
        "R520", // 116
        "R521", // 117
        "R522", // 118
        "R523", // 119
        "R620", // 120
        "R621", // 121
        "R622", // 122
        "R623", // 123
        "R720", // 124
        "R721", // 125
        "R722", // 126
        "R723", // 127
    }
};

const char *register_name(vfpu_register reg)
{
    // https://github.com/hrydgard/ppsspp/blob/748eef05d0c64b7aa5be6714fa52fa84a5977f05/Core/MIPS/MIPSVFPUUtils.cpp#L531 
    if (reg.size == vfpu_size::Single)
    {
        if (reg.num >= 128 && reg.num < 128 + MAX_CONTROL_REGISTERS)
            return _vfpu_control_register_names[reg.num - 128];
        else if (reg.num == 255)
            return "(interlock)";
    }

    if (reg.num >= 128)
    {
        return "?";
    }

	return _vfpu_register_names[value(reg.size)][reg.num]; 
}

static const char *_vfpu_matrix_names[3][128] = {
    { // Pair
        "M000", // 0
        "M010", // 1
        "M020", // 2
        "M030", // 3
        "M100", // 4
        "M110", // 5
        "M120", // 6
        "M130", // 7
        "M200", // 8
        "M210", // 9
        "M220", // 10
        "M230", // 11
        "M300", // 12
        "M310", // 13
        "M320", // 14
        "M330", // 15
        "M400", // 16
        "M410", // 17
        "M420", // 18
        "M430", // 19
        "M500", // 20
        "M510", // 21
        "M520", // 22
        "M530", // 23
        "M600", // 24
        "M610", // 25
        "M620", // 26
        "M630", // 27
        "M700", // 28
        "M710", // 29
        "M720", // 30
        "M730", // 31
        "E000", // 32
        "E001", // 33
        "E002", // 34
        "E003", // 35
        "E100", // 36
        "E101", // 37
        "E102", // 38
        "E103", // 39
        "E200", // 40
        "E201", // 41
        "E202", // 42
        "E203", // 43
        "E300", // 44
        "E301", // 45
        "E302", // 46
        "E303", // 47
        "E400", // 48
        "E401", // 49
        "E402", // 50
        "E403", // 51
        "E500", // 52
        "E501", // 53
        "E502", // 54
        "E503", // 55
        "E600", // 56
        "E601", // 57
        "E602", // 58
        "E603", // 59
        "E700", // 60
        "E701", // 61
        "E702", // 62
        "E703", // 63
        "M002", // 64
        "M012", // 65
        "M022", // 66
        "M032", // 67
        "M102", // 68
        "M112", // 69
        "M122", // 70
        "M132", // 71
        "M202", // 72
        "M212", // 73
        "M222", // 74
        "M232", // 75
        "M302", // 76
        "M312", // 77
        "M322", // 78
        "M332", // 79
        "M402", // 80
        "M412", // 81
        "M422", // 82
        "M432", // 83
        "M502", // 84
        "M512", // 85
        "M522", // 86
        "M532", // 87
        "M602", // 88
        "M612", // 89
        "M622", // 90
        "M632", // 91
        "M702", // 92
        "M712", // 93
        "M722", // 94
        "M732", // 95
        "E020", // 96
        "E021", // 97
        "E022", // 98
        "E023", // 99
        "E120", // 100
        "E121", // 101
        "E122", // 102
        "E123", // 103
        "E220", // 104
        "E221", // 105
        "E222", // 106
        "E223", // 107
        "E320", // 108
        "E321", // 109
        "E322", // 110
        "E323", // 111
        "E420", // 112
        "E421", // 113
        "E422", // 114
        "E423", // 115
        "E520", // 116
        "E521", // 117
        "E522", // 118
        "E523", // 119
        "E620", // 120
        "E621", // 121
        "E622", // 122
        "E623", // 123
        "E720", // 124
        "E721", // 125
        "E722", // 126
        "E723", // 127
    },

    { // Triple
        "M000", // 0
        "M010", // 1
        "M020", // 2
        "M030", // 3
        "M100", // 4
        "M110", // 5
        "M120", // 6
        "M130", // 7
        "M200", // 8
        "M210", // 9
        "M220", // 10
        "M230", // 11
        "M300", // 12
        "M310", // 13
        "M320", // 14
        "M330", // 15
        "M400", // 16
        "M410", // 17
        "M420", // 18
        "M430", // 19
        "M500", // 20
        "M510", // 21
        "M520", // 22
        "M530", // 23
        "M600", // 24
        "M610", // 25
        "M620", // 26
        "M630", // 27
        "M700", // 28
        "M710", // 29
        "M720", // 30
        "M730", // 31
        "E000", // 32
        "E001", // 33
        "E002", // 34
        "E003", // 35
        "E100", // 36
        "E101", // 37
        "E102", // 38
        "E103", // 39
        "E200", // 40
        "E201", // 41
        "E202", // 42
        "E203", // 43
        "E300", // 44
        "E301", // 45
        "E302", // 46
        "E303", // 47
        "E400", // 48
        "E401", // 49
        "E402", // 50
        "E403", // 51
        "E500", // 52
        "E501", // 53
        "E502", // 54
        "E503", // 55
        "E600", // 56
        "E601", // 57
        "E602", // 58
        "E603", // 59
        "E700", // 60
        "E701", // 61
        "E702", // 62
        "E703", // 63
        "M001", // 64
        "M011", // 65
        "M021", // 66
        "M031", // 67
        "M101", // 68
        "M111", // 69
        "M121", // 70
        "M131", // 71
        "M201", // 72
        "M211", // 73
        "M221", // 74
        "M231", // 75
        "M301", // 76
        "M311", // 77
        "M321", // 78
        "M331", // 79
        "M401", // 80
        "M411", // 81
        "M421", // 82
        "M431", // 83
        "M501", // 84
        "M511", // 85
        "M521", // 86
        "M531", // 87
        "M601", // 88
        "M611", // 89
        "M621", // 90
        "M631", // 91
        "M701", // 92
        "M711", // 93
        "M721", // 94
        "M731", // 95
        "E010", // 96
        "E011", // 97
        "E012", // 98
        "E013", // 99
        "E110", // 100
        "E111", // 101
        "E112", // 102
        "E113", // 103
        "E210", // 104
        "E211", // 105
        "E212", // 106
        "E213", // 107
        "E310", // 108
        "E311", // 109
        "E312", // 110
        "E313", // 111
        "E410", // 112
        "E411", // 113
        "E412", // 114
        "E413", // 115
        "E510", // 116
        "E511", // 117
        "E512", // 118
        "E513", // 119
        "E610", // 120
        "E611", // 121
        "E612", // 122
        "E613", // 123
        "E710", // 124
        "E711", // 125
        "E712", // 126
        "E713", // 127
    },

    { // Quad
        "M000", // 0
        "M010", // 1
        "M020", // 2
        "M030", // 3
        "M100", // 4
        "M110", // 5
        "M120", // 6
        "M130", // 7
        "M200", // 8
        "M210", // 9
        "M220", // 10
        "M230", // 11
        "M300", // 12
        "M310", // 13
        "M320", // 14
        "M330", // 15
        "M400", // 16
        "M410", // 17
        "M420", // 18
        "M430", // 19
        "M500", // 20
        "M510", // 21
        "M520", // 22
        "M530", // 23
        "M600", // 24
        "M610", // 25
        "M620", // 26
        "M630", // 27
        "M700", // 28
        "M710", // 29
        "M720", // 30
        "M730", // 31
        "E000", // 32
        "E001", // 33
        "E002", // 34
        "E003", // 35
        "E100", // 36
        "E101", // 37
        "E102", // 38
        "E103", // 39
        "E200", // 40
        "E201", // 41
        "E202", // 42
        "E203", // 43
        "E300", // 44
        "E301", // 45
        "E302", // 46
        "E303", // 47
        "E400", // 48
        "E401", // 49
        "E402", // 50
        "E403", // 51
        "E500", // 52
        "E501", // 53
        "E502", // 54
        "E503", // 55
        "E600", // 56
        "E601", // 57
        "E602", // 58
        "E603", // 59
        "E700", // 60
        "E701", // 61
        "E702", // 62
        "E703", // 63
        "M002", // 64
        "M012", // 65
        "M022", // 66
        "M032", // 67
        "M102", // 68
        "M112", // 69
        "M122", // 70
        "M132", // 71
        "M202", // 72
        "M212", // 73
        "M222", // 74
        "M232", // 75
        "M302", // 76
        "M312", // 77
        "M322", // 78
        "M332", // 79
        "M402", // 80
        "M412", // 81
        "M422", // 82
        "M432", // 83
        "M502", // 84
        "M512", // 85
        "M522", // 86
        "M532", // 87
        "M602", // 88
        "M612", // 89
        "M622", // 90
        "M632", // 91
        "M702", // 92
        "M712", // 93
        "M722", // 94
        "M732", // 95
        "E020", // 96
        "E021", // 97
        "E022", // 98
        "E023", // 99
        "E120", // 100
        "E121", // 101
        "E122", // 102
        "E123", // 103
        "E220", // 104
        "E221", // 105
        "E222", // 106
        "E223", // 107
        "E320", // 108
        "E321", // 109
        "E322", // 110
        "E323", // 111
        "E420", // 112
        "E421", // 113
        "E422", // 114
        "E423", // 115
        "E520", // 116
        "E521", // 117
        "E522", // 118
        "E523", // 119
        "E620", // 120
        "E621", // 121
        "E622", // 122
        "E623", // 123
        "E720", // 124
        "E721", // 125
        "E722", // 126
        "E723", // 127
    },
};

const char *matrix_name(vfpu_matrix mat)
{
    if (mat.num > 127 || mat.size == vfpu_size::Single || mat.size == vfpu_size::Invalid)
    {
        return "?";
    }

	return _vfpu_matrix_names[value(mat.size)-1][mat.num]; 
}

static const char *_vfpu_size_names[] = {".s", ".p", ".t", ".q", "%"};

const char *size_suffix(vfpu_size sz)
{
    return _vfpu_size_names[value(sz)];
}

const char *size_suffix(u32 opcode)
{
    return size_suffix(get_vfpu_size(opcode));
}

static const char *_vfpu_condition_names[] = {
    "FL","EQ","LT","LE","TR","NE","GE","GT",
    "EZ","EN","EI","ES","NZ","NN","NI","NS"
};

const char *vfpu_condition_name(vfpu_condition cond)
{
    return _vfpu_condition_names[value(cond)];
}

static const char *_vfpu_constant_names[] = {
    "(undefined)",
    "MaxFloat",
    "Sqrt(2)",
    "Sqrt(1/2)",
    "2/Sqrt(PI)",
    "2/PI",
    "1/PI",
    "PI/4",
    "PI/2",
    "PI",
    "e",
    "Log2(e)",
    "Log10(e)",
    "ln(2)",
    "ln(10)",
    "2*PI",
    "PI/6",
    "Log10(2)",
    "Log2(10)",
    "Sqrt(3)/2"
};

const char *vfpu_constant_name(vfpu_constant constant)
{
    return _vfpu_constant_names[value(constant)];
}

static const char *_vfpu_prefix_names[] = {
    "x",
    "y",
    "z",
    "w",
    "-x",
    "-y",
    "-z",
    "-w",
    "|x|",
    "|y|",
    "|z|",
    "|w|",
    "-|x|",
    "-|y|",
    "-|z|",
    "-|w|",
    "0",
    "1",
    "2",
    "1/2",
    "3",
    "1/3",
    "1/4",
    "1/6"
};

const char *vfpu_prefix_name(vfpu_prefix pfx)
{
    assert(value(pfx) < value(vfpu_prefix::_MAX));
    return _vfpu_prefix_names[value(pfx)];
}

static const char *_vfpu_destination_prefix_names[] = {
    "",
    "0:1",
    "X",
    "-1:1",
    "M",
    "0:1M",
    "XM",
    "-1:1M"
};

const char *vfpu_destination_prefix_name(vfpu_destination_prefix pfx)
{
    assert(value(pfx) < value(vfpu_destination_prefix::_MAX));
    return _vfpu_destination_prefix_names[value(pfx)];
}

static const char *_vfpu_rotation_names[] = {
    "0",
    "c",
    "s",
    "-s"
};

const char *vfpu_rotation_name(vfpu_rotation rot)
{
    assert(value(rot) < value(vfpu_rotation::_MAX));

    return _vfpu_rotation_names[value(rot)];
}
