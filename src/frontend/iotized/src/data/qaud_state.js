import {useState} from "react";
import {createEnum} from "./common";

export const EFFECT_STATE = createEnum(
    "INITIAL",
    "STARTED",
    "SUCCESS",
    "FAILED",
);

export const createQuadState = (sideEffect) => {
    const initialState = {state: EFFECT_STATE.INITIAL};
    const [{state, data, error}, setState] = useState(initialState)
    const updateState = (delta) => setState({state, data, error, ...delta});

    const reset = () => setState(initialState);

    const trigger = async (...args) => {
        updateState({
            data: null,
            error: null,
            state: EFFECT_STATE.STARTED,
        });

        try {
            const newData = await sideEffect(...args);
            updateState({state: EFFECT_STATE.SUCCESS, data: newData,});
        } catch (e) {
            updateState({state: EFFECT_STATE.FAILED, error: e,});
        }
    };
    return {
        state, data, error, trigger, reset,
        isInitial: state === EFFECT_STATE.INITIAL,
        isInProgress: state === EFFECT_STATE.STARTED,
        isSuccess: state === EFFECT_STATE.SUCCESS,
        isFailed: state === EFFECT_STATE.FAILED,
    };
};
