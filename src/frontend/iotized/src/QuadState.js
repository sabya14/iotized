import {createQuadState} from "./data/qaud_state";
import React, {Fragment} from "react";


export const QuadStateView = ({
                                  sideEffectFn,
                                  initComponentFn = () => (<></>),
                                  inProgressComponentFn = () => (<> Loading </>),
                                  successComponentFn = (r) => <pre>{JSON.stringify(r?.data, null, 2)}</pre>,
                                  errorComponentFn = (r) => <pre>{JSON.stringify(r?.error, null, 2)}</pre>,
                              }) => {
    const {trigger, reset, ...result} = createQuadState(sideEffectFn);

    if (result.isInitial) {
        return initComponentFn(result, trigger, reset);
    }

    if (result.isInProgress) {
        return inProgressComponentFn(result, trigger, reset);
    }

    if (result.isSuccess) {
        return successComponentFn(result, trigger, reset);
    }

    if (result.isFailed) {
        return errorComponentFn(result, trigger, reset);
    }

    return (<Fragment> "UNKNOWN STATE: {result?.state?.toString()} " </Fragment>)
}
