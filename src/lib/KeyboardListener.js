export const KEY_CODES = {
  ARROW_LEFT: 37,
  ARROW_UP: 38,
  ARROW_RIGHT: 39,
  ARROW_DOWN: 40,
  I: 73,
  P: 80,
  ENTER: 13,
};

export const makeKeydownListener = (keyCode, listener = () => {}) => {
  document.addEventListener('keydown', (ev) => {
    if (ev.keyCode !== keyCode) {
      return;
    }

    listener(ev);
  });
};
