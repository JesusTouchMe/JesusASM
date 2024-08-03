package cum.jesus.jesusasm.parser

import cum.jesus.jesusasm.util.WriteOnceProperty

class MetaData {
    var module by WriteOnceProperty("")
    var stack by WriteOnceProperty(0u)
    var entry by WriteOnceProperty("")
}