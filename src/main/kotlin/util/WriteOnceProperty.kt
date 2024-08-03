package cum.jesus.jesusasm.util

import kotlin.properties.ReadWriteProperty
import kotlin.reflect.KProperty

class WriteOnceProperty<T>(default: T) : ReadWriteProperty<Any?, T> {
    private var value: T = default
    private var locked = false

    override fun getValue(thisRef: Any?, property: KProperty<*>): T {
        return value
    }

    override fun setValue(thisRef: Any?, property: KProperty<*>, value: T) {
        if (locked) throw RuntimeException("property can only be set once")

        this.value = value
        locked = true
    }
}