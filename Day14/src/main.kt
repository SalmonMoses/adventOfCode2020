import java.io.File

val maskRegex = Regex("mask = ([X10]{36})")
val memoryValueRegex = Regex("mem\\[([(0-9)]+)] = ([0-9]+)")

fun applyMask(number: ULong, mask: String): ULong {
    val numberString = number.toString(2).padStart(36, '0');
    var resultString = ""
    for (i in mask.indices) {
        resultString += if (mask[i] == 'X') numberString[i] else mask[i]
    }
    return resultString.toULong(2)
}

fun applyFluctuatingMask(number: ULong, mask: String): Array<ULong> {
    val numberString = number.toString(2).padStart(36, '0')
    var resultStrings = mutableListOf("")
    for (i in mask.indices) {
        val transitive = resultStrings.toMutableList()
        when (mask[i]) {
            'X' -> resultStrings.forEachIndexed { j, str ->
                transitive += str + '1'
                transitive[j] = str + '0'
            }
            '0' -> resultStrings.forEachIndexed { j, str ->
                transitive[j] = str + numberString[i]
            }
            '1' -> resultStrings.forEachIndexed { j, str ->
                transitive[j] = str + mask[i]
            }
        }
        resultStrings = transitive
    }
    return resultStrings.map { it.toULong(2) }.toTypedArray()
}

fun taskOne(): ULong {
    var curMask = ""
    val memory: HashMap<ULong, ULong> = hashMapOf()
    val lines = File("resources/input.txt").readLines()
    for (line in lines) {
        if (line matches memoryValueRegex) {
            val matchResult = memoryValueRegex.matchEntire(line)!!
            val address = matchResult.groupValues[1].toULong()
            memory[address] = applyMask(matchResult.groupValues[2].toULong(), curMask)
        } else if (line matches maskRegex) {
            curMask = maskRegex.matchEntire(line)!!.groupValues[1]
        }
    }
    return memory.values.reduce(ULong::plus)
}

fun taskTwo(): ULong {
    var curMask = ""
    val memory: HashMap<ULong, ULong> = hashMapOf()
    val lines = File("resources/input.txt").readLines()
    for (line in lines) {
        if (line matches memoryValueRegex) {
            val matchResult = memoryValueRegex.matchEntire(line)!!
            val address = applyFluctuatingMask(matchResult.groupValues[1].toULong(), curMask)
            val value = matchResult.groupValues[2].toULong()
            for (i in address.indices) {
                memory[address[i]] = value
            }
        } else if (line matches maskRegex) {
            curMask = maskRegex.matchEntire(line)!!.groupValues[1]
        }
    }
    return memory.values.reduce(ULong::plus)
}

fun main() {
    val path = System.getProperty("user.dir")
    println("Working Directory = $path")

    println(taskOne())
    println(taskTwo())
}