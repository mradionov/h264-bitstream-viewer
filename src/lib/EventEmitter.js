class EventEmitter {
  constructor() {
    this.listeners = {};
  }

  addEventListener(name, listenerToAdd) {
    this.listeners[name] = this.listeners[name] || [];
    this.listeners[name].push(listenerToAdd);

    return this;
  }

  removeEventListener(name, listenerToRemove) {
    if (this.listeners[name] === undefined) {
      return;
    }

    this.listeners[name] = this.listeners[name].filter((listener) => {
      return listener !== listenerToRemove;
    });

    return this;
  }

  emit(name, ...args) {
    if (this.listeners[name] === undefined) {
      return;
    }

    this.listeners[name].forEach((listener) => {
      listener(...args);
    });

    return this;
  }
}

export default EventEmitter;
