import { OpenMCT } from 'openmct/dist/openmct';
import { http } from '../core/http';
import { TelemetryRequest } from 'openmct/dist/src/api/telemetry/TelemetryAPI';
import { AugmentedDomainObject } from '../types/AugmentedDomainObject';

export function HistoricalTelemetryPlugin() {
  return function install(openmct: OpenMCT) {
    const provider = {
      supportsRequest: function (domainObject: AugmentedDomainObject) {
        return domainObject.podId !== undefined;
      },
      request: function (
        domainObject: AugmentedDomainObject,
        options: TelemetryRequest,
      ) {
        // TODOLater: work out how to type this
        // eslint-disable-next-line @typescript-eslint/no-unsafe-assignment
        const { start, end } = options;
        const podId = domainObject.podId;
        const measurementKey = domainObject.identifier.key;
        // eslint-disable-next-line @typescript-eslint/restrict-template-expressions
        const url = `openmct/data/historical/pods/${podId}/measurements/${measurementKey}?start=${start}&end=${end}`;

        return http
          .get(url)
          .json()
          .then((data) => data);
      },
    };

    openmct.telemetry.addProvider(provider);
  };
}
